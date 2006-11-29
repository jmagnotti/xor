#ifndef __IMMERGE_C_
#define __IMMERGE_C_ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <mpi.h>

#include "immerge.h"

#ifdef __cplusplus
extern "C" {
#endif

double IMM_MAXNUMX = 9;
double IMM_REALNUMX = 4;
double IMM_REALNUMY = 2;
double IMM_WINDOWBORDER_X=1.0;
double IMM_WINDOWBORDER_Y=1.0;
double IMM_LEFTOFFSET=0;
                                                                                                                                                             
/* global structs are cleaner than global variables... */
struct igGlut    igg;
struct igMpi     igm;
struct iData     idd;
                                                                                                                                                             
/* temporary variables, used a lot */
int iFlag;
//int i,j,k;
                                                                                                                                                             
#include "iconfig.h"


/* Shutdown and exit */
static void do_shutdown(void)  {
	printf("Node%i: Finalize...",igm.myrank);

	/* removed MPI_Finalize because master was hanging
	 * due to uncaught mpi_send buffers 
         */
/*	MPI_Finalize();
 */
	printf("Quitting...exit.\n");
	exit(0);
}

/* Send some command to all nodes and wait for them to receive it */
int iSendToAll(struct iMsg cmd) {
	int i;
	/* Send message asyncronously */
        for (i=1; i<igm.ntasks; i++) {
                MPI_Isend(&cmd.command, IMM_MSGSIZE, 
			MPI_FLOAT, i, MSGTAG, MPI_COMM_WORLD, 
			&igm.masterrequest[i-1]);
        }

        /* Wait for everyone to receive it */
        MPI_Waitall(igm.ntasks-1, igm.masterrequest, igm.masterstatus);

	/* no problems, return */
	return 0;
}

int iSendToMaster(struct iMsg cmd) {
	MPI_Send(&cmd.command, IMM_MSGSIZE, MPI_FLOAT, 
		0, MSGTAG, MPI_COMM_WORLD);
	return 0;
}


void iCalcLookat() {
	float temp, tempr, ytheta;

	idd.lookaty = 0;

	temp = (idd.numx -  (idd.nx + 1) + idd.rightoffset) * idd.theta + idd.theta/ 2.0;

	tempr = temp * M_PI / 180.0;

	idd.lookatx = cos(tempr);
	idd.lookatz = -sin(tempr);

	temp = (idd.ny - (idd.numy+1)/2.0) * idd.theta;

	tempr = temp * M_PI / 180.0;

	idd.lookaty = sin(tempr);
}

/* Window reshape calls this */
static void iReshape(int width, int height)
{

	float temp, tempr;
/*			printf("reshape: (%f, %f) \n", IMM_WINDOWBORDER_X, IMM_WINDOWBORDER_Y);
*/
    igg.windW = (GLint)width;
    igg.windH = (GLint)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (idd.iMode == IMM_MODE_2D || idd.iMode == IMM_MODE_2D_WINDOW || idd.iMode == IMM_MODE_2D_SHRINK) {

	if (idd.iMode == IMM_MODE_2D_SHRINK) {

		idd.xr = idd.xmax - idd.xmin;
		idd.yr = idd.ymax - idd.ymin;

		idd.xmin = idd.xmin*(idd.numx/(float)idd.numy) - idd.xr*(idd.numx/(float)idd.numy - 1)/2.0;
		idd.xmax = idd.xmax*(idd.numx/(float)idd.numy) - idd.xr*(idd.numx/(float)idd.numy - 1)/2.0;
/*
		idd.ymin = idd.ymin*(idd.numx/(float)idd.numy) - idd.yr*(idd.numx/(float)idd.numy - 1)/2.0;
		idd.ymax = idd.ymax*(idd.numx/(float)idd.numy) - idd.yr*(idd.numx/(float)idd.numy - 1)/2.0;
*/
		idd.xr = idd.xmax - idd.xmin;
		idd.yr = idd.ymax - idd.ymin;
	}

	if (igm.myrank == 0) {
		idd.myxmin = idd.xmin;
		idd.myxmax = idd.xmax;

		idd.myymin = idd.ymin;
		idd.myymax = idd.ymax;

		idd.myzmin = idd.zmin;
		idd.myzmax = idd.zmax;

 	} else {
		if ( idd.iMode == IMM_MODE_2D_WINDOW) {

			idd.myxmin = (idd.xr/(float)idd.numx)*((float)idd.nx-0.0) + idd.xmin;
			idd.myxmax = (idd.xr/(float)idd.numx)*((float)idd.nx+1.0) + idd.xmin;
	
			idd.myymin = (idd.yr/(float)idd.numy)*((float)idd.ny-1.0) + idd.ymin;
			idd.myymax = (idd.yr/(float)idd.numy)*((float)idd.ny+0.0) + idd.ymin;
	
			idd.myzmin = (idd.zr/(float)idd.numz)*((float)idd.nz-1.0) + idd.zmin;
			idd.myzmax = (idd.zr/(float)idd.numz)*((float)idd.nz+0.0) + idd.zmin;


		} else {

			idd.myxmin = (idd.xr/(float)idd.numx)*((float)idd.nx-0.0) + idd.xmin;
			idd.myxmax = (idd.xr/(float)idd.numx)*((float)idd.nx+1.0) + idd.xmin;
	
			idd.myymin = (idd.yr/(float)idd.numy)*((float)idd.ny-1.0) + idd.ymin;
			idd.myymax = (idd.yr/(float)idd.numy)*((float)idd.ny+0.0) + idd.ymin;
	
			idd.myzmin = (idd.zr/(float)idd.numz)*((float)idd.nz-1.0) + idd.zmin;
			idd.myzmax = (idd.zr/(float)idd.numz)*((float)idd.nz+0.0) + idd.zmin;

		}
	}


	gluOrtho2D(	idd.myxmin,
			idd.myxmax,
			idd.myymin,
			idd.myymax
		  );

    }

    if (idd.iMode == IMM_MODE_3D_WRAP || idd.iMode == IMM_MODE_3D_PERSPECTIVE) {

	if (igm.myrank == 0) {
		if (idd.iMode == IMM_MODE_3D_PERSPECTIVE)
			gluPerspective(180.0/M_PI*atan((idd.realnumx/idd.realnumy)*tan(idd.xmax*M_PI/180.0)), 
					(idd.realnumx/idd.realnumy), idd.zmin, idd.zmax);
		else 
			glFrustum(idd.xmin, idd.xmax, idd.ymin, idd.ymax, idd.zmin, idd.zmax);

		iCalcLookat();
		gluLookAt(	idd.eyex, 	idd.eyey, 	idd.eyez, 
				idd.lookatx, 	idd.lookaty, 	idd.lookatz,
				idd.upx, 	idd.upy, 	idd.upz);

	} else {

		idd.myxmin = (idd.zmin * cos( M_PI / 2.0 + idd.thetar/2.0));
		idd.myxmax = (idd.zmin * cos( M_PI / 2.0 - idd.thetar/2.0));

		idd.myymin = (idd.zmin * cos( M_PI / 2.0 + idd.thetar/2.0));
		idd.myymax = (idd.zmin * cos( M_PI / 2.0 - idd.thetar/2.0));
/*
		idd.myymin = (idd.yr/(float)idd.numy)*((float)idd.ny+0.0) + idd.ymin;
		idd.myymax = (idd.yr/(float)idd.numy)*((float)idd.ny+1.0) + idd.ymin;

*/
		idd.myzmin = idd.zmin;
		idd.myzmax = idd.zmax;

		if (idd.iMode == IMM_MODE_3D_PERSPECTIVE) {


			idd.myfovx = (180.0/M_PI* 
					atan((idd.realnumx/idd.realnumy) * tan( idd.fovx/2 * M_PI/180.0 ) ) ) *2/idd.numx;

			idd.theta = idd.myfovx;
			idd.thetar = idd.theta *M_PI/180.0;
			idd.rightoffset = ((180.0 / idd.theta) - idd.realnumx) / 2.0 ;
			idd.aspectratio = (idd.realnumx/idd.realnumy) * idd.numy/idd.numx;

			gluPerspective(idd.myfovx * IMM_WINDOWBORDER_X, idd.aspectratio, idd.zmin, idd.zmax); 

		} else {
			glFrustum(	idd.myxmin * IMM_WINDOWBORDER_X,
					idd.myxmax * IMM_WINDOWBORDER_X,
					idd.myymin * IMM_WINDOWBORDER_Y,
					idd.myymax * IMM_WINDOWBORDER_Y,
					idd.myzmin,
					idd.myzmax
				  );
		}

		iCalcLookat();
	
	 	if (idd.iMode == IMM_MODE_3D_PERSPECTIVE) {

			if (idd.ny==5)
				glRotatef(-2*idd.myfovx * idd.aspectratio, 1, 0, 0);
			if (idd.ny==4)
				glRotatef(-idd.myfovx * idd.aspectratio, 1, 0, 0);
			if (idd.ny==3)
				glRotatef(0, 1, 0, 0);
			if (idd.ny==2)
				glRotatef(idd.myfovx * idd.aspectratio, 1, 0, 0);
			if (idd.ny==1)
				glRotatef(2*idd.myfovx * idd.aspectratio, 1, 0, 0);

			idd.lookaty = 0;
		}

		glPushMatrix();

		gluLookAt(	idd.eyex, 	idd.eyey, 	idd.eyez, 
				idd.lookatx, 	idd.lookaty, 	idd.lookatz,
				idd.upx, 	idd.upy, 	idd.upz);


		glPushMatrix();

		glRotatef(idd.myrx, 1, 0, 0);
		glRotatef(idd.myry, 0, 1, 0);
		glRotatef(idd.myrz, 0, 0, 1);
		glTranslatef(idd.myx, idd.myy, idd.myz);
	}
    }

    glMatrixMode(GL_MODELVIEW);

       if (idd.reshapeFunc != NULL)
                idd.reshapeFunc(width,height);
}

int iMyrank() {
	return igm.myrank;
}

int iNtasks() {
	return igm.ntasks;
}

int iXrank() {
	return (int)idd.nx;
}

int iYrank() {
	return (int)idd.ny;
}

/* Process command line arguments */
static GLenum iArgs(int *argc, char **argv)
{
    GLint i;

    igg.doubleBuffer = GL_TRUE;

    for (i = 1; i < *argc; i++) {
	if (strcmp(argv[i], "-sb") == 0) {
	    igg.doubleBuffer = GL_FALSE;
	} else if (strcmp(argv[i], "-db") == 0) {
	    igg.doubleBuffer = GL_TRUE;
	}
    }
    return GL_TRUE;
}

/* slave node idle function. */
/* This is called as much as possible from Glut.
 * Calls Asynconous mpi receive and then tests until 
 * a message is received.  When it is, process it.
 */

void iIdle(void) {
	/* isWaiting is true when we've called the receive function
         * and are waiting for a message.
         */

	if  (igm.isWaiting == 0) {

		igm.isWaiting = 1;

		/* Asyncronous receive, save in gm.request */
		MPI_Irecv(&igm.slave.command, IMM_MSGSIZE, MPI_FLOAT, MPI_ANY_SOURCE, 
			MSGTAG, MPI_COMM_WORLD, &igm.slaverequest);

	} else {

		/* Test to see if the gm.request has been satisfied.  
		 * MPI_Test sets iFlag if the it has. 
                 */
		MPI_Test(&igm.slaverequest, &iFlag, &igm.slavestatus);

		/* If we've received a message... */
		if (iFlag) {

			/* We want to call Irecv again next time around */
			igm.isWaiting=0;

			/* What kind of message do we have? */
			switch ((int)igm.slave.command[0]) {
				case IMM_SHUTDOWN:
					/* IMM_SHUTDOWN == shutdown, end */
					iSendToMaster(igm.slave);

					do_shutdown();
					break;

				case IMM_REFRESH:
					/* IMM_REFRESH == manual refresh */
					glutPostRedisplay();
					break;

				case IMM_UPDATE_WORLD:
					/* IMM_UPDATE_WORLD == update world
					 */
					/* world update */
					if (idd.worldFunc != NULL)
						idd.worldFunc(igm.myrank, igm.ntasks, &igm.slave);

					break;

				case IMM_UPDATE_FRAME:

					/* Display update */
					glutPostRedisplay();

					/* And call MPI_Barrier to wait until EVERYONE
					 * has received this message.
					 */
					MPI_Barrier(MPI_COMM_WORLD);

					break;
				case 5:
					idd.myx 	= igm.slave.command[1];
					idd.myy 	= igm.slave.command[2];
					idd.myz		= igm.slave.command[3];
					idd.myrx 	= igm.slave.command[4];
					idd.myry 	= igm.slave.command[5];
					idd.myrz	= igm.slave.command[6];

					iReshape (igg.windW, igg.windH);
					break;

				case 6:
					idd.rightoffset = igm.slave.command[1];

					iReshape (igg.windW, igg.windH);
					break;
				case 10:
					IMM_WINDOWBORDER_X = igm.slave.command[1];
					IMM_WINDOWBORDER_Y = igm.slave.command[2];
					iReshape (igg.windW, igg.windH);
					break;					
				default:
					/* See if client cares about it */
					if (idd.worldFunc != NULL)
						idd.worldFunc(igm.myrank, igm.ntasks, &igm.slave);
					break;
			}
		}
	}

	if (idd.idleFunc != NULL)
		idd.idleFunc();	
}

/* Master special key callback */
static void iMasterSpecialKey(int key, int x, int y)
{
	int i;
	int send = 1, move = 0;

	switch (key) {
		case GLUT_KEY_F1:
			idd.rightoffset += 0.25;

			igm.master.command[0] = 6;
			igm.master.command[1] = idd.rightoffset;

			iReshape (igg.windW, igg.windH);

			break;
		case GLUT_KEY_F2:
			idd.rightoffset -= 0.25;

			igm.master.command[0] = 6;
			igm.master.command[1] = idd.rightoffset;

			iReshape (igg.windW, igg.windH);

			break;

		case GLUT_KEY_RIGHT:
			idd.myx -= IMM_MOVE_D;
			move=1;

			break;
		case GLUT_KEY_LEFT:
			idd.myx += IMM_MOVE_D;
			move=1;

			break;
		case GLUT_KEY_UP:
			idd.myy -= IMM_MOVE_D;
			move=1;

			break;
		case GLUT_KEY_DOWN:
			idd.myy += IMM_MOVE_D;
			move=1;

			break;
		case GLUT_KEY_F5:
			idd.myz -= IMM_MOVE_D;
			move=1;

			break;
		case GLUT_KEY_F6:
			idd.myz += IMM_MOVE_D;
			move=1;
			
			break;
		case GLUT_KEY_INSERT:
			idd.myrz -= 5;
			move=1;

			break;
		case GLUT_KEY_PAGE_UP:
			idd.myrz += 5;
			move=1;

			break;

		case GLUT_KEY_PAGE_DOWN:
			idd.myry += 5;
			move=1;

			break;
		case GLUT_KEY_END:
			idd.myrx -= 5;
			move=1;

			break;
		case GLUT_KEY_HOME:
			idd.myrx += 5;
			move=1;
			
			break;
		default:
			send = 0;
			break;
	}
	if (move) {
				igm.master.command[0] = 5;
				igm.master.command[1] = idd.myx;
				igm.master.command[2] = idd.myy;
				igm.master.command[3] = idd.myz;
				igm.master.command[4] = idd.myrx;
				igm.master.command[5] = idd.myry;
				igm.master.command[6] = idd.myrz;
				iReshape (igg.windW, igg.windH);
	}

    if (send) {
	/* If a message is to be sent, sent it to all nodes */
	iSendToAll(igm.master);

	/* And reset the message buffer for next time */
	for (i=0; i<IMM_MSGSIZE; i++) {
		igm.slave.command[i]=0;
		igm.master.command[i]=0;
	}
    }


	if (idd.specialFunc != NULL)
		idd.specialFunc(key, x, y);
}

/* Master key callback */
/* Main controller of nodes...
 * When a key is pressed, this function is called
 * and it is processed to change variables as appropriate
 * and notify nodes as appropriate
 */
static void iMasterKey(unsigned char key, int x, int y)
{
	int i;
	int  send=1;
    /* Which key was pressed? */
    switch (key) {
			case 'q':
			case 27:
				/* 'q' or ESC (27) == shutdown */

				/* set the shutdown command and data */
				igm.master.command[0]=IMM_SHUTDOWN;
				igm.master.command[1]=IMM_SHUTDOWN;

				printf("Shutting down...\n");

				/* Send all nodes the shutdown message */
				iSendToAll(igm.master);

			        for (i=1; i<igm.ntasks; i++) {
			                MPI_Irecv(&igm.master.command, IMM_MSGSIZE, 
						MPI_FLOAT, i, MSGTAG, MPI_COMM_WORLD, 
						&igm.masterrequest[i-1]);
			        }

			        /* Wait for everyone to finish */
			        MPI_Waitall(igm.ntasks-1, igm.masterrequest, igm.masterstatus);
				
				printf("Nodes are done.\n");

				/* Master quits program */
				do_shutdown();
				break;

			case 'r':
				/* Manual refresh, set refresh command */
				igm.master.command[0]=IMM_REFRESH;
				igm.master.command[1]=IMM_REFRESH;
				break;

			case 0x7f:	 /* DELETE KEY */
				idd.myry -= 5;

				igm.master.command[0] = 5;
				igm.master.command[1] = idd.myx;
				igm.master.command[2] = idd.myy;
				igm.master.command[3] = idd.myz;
				igm.master.command[4] = idd.myrx;
				igm.master.command[5] = idd.myry;
				igm.master.command[6] = idd.myrz;
				iReshape (igg.windW, igg.windH);
			
				break;
			case 'p':
				printf("myx %f, myy %f, myz %f, myrx %f, myry %f, myrz %f\n", idd.myx, idd.myy, 
						idd.myz, idd.myrx, idd.myry, idd.myrz);
				break;
/*		        case 'd':
		                IMM_WINDOWBORDER_X+=.001;
	                        iReshape(igg.windW, igg.windH);
				igm.master.command[0] = 10;
				igm.master.command[1] = IMM_WINDOWBORDER_X;
				igm.master.command[2] = IMM_WINDOWBORDER_Y;
		                break;
		        case 'a':
		                IMM_WINDOWBORDER_X-=.001;
	                        iReshape(igg.windW, igg.windH);
				igm.master.command[0] = 10;
				igm.master.command[1] = IMM_WINDOWBORDER_X;
				igm.master.command[2] = IMM_WINDOWBORDER_Y;
		                break;
		        case 'w':
		                IMM_WINDOWBORDER_Y+=.001;
	                        iReshape(igg.windW, igg.windH);
				igm.master.command[0] = 10;
				igm.master.command[1] = IMM_WINDOWBORDER_X;
				igm.master.command[2] = IMM_WINDOWBORDER_Y;
		                break;
		        case 'W':
		                IMM_WINDOWBORDER_Y-=.001;
	                        iReshape(igg.windW, igg.windH);
				igm.master.command[0] = 10;
				igm.master.command[1] = IMM_WINDOWBORDER_X;
				igm.master.command[2] = IMM_WINDOWBORDER_Y;
		                break;
*/
		      default:
				/* Other keys should be ignored */
				send=0;
				break;
    }
    if (send) {
	/* If a message is to be sent, sent it to all nodes */
	iSendToAll(igm.master);

	/* And reset the message buffer for next time */
	for (i=0; i<IMM_MSGSIZE; i++) {
		igm.slave.command[i]=0;
		igm.master.command[i]=0;
	}
    }

	/* Relay to client */
	if (idd.keyboardFunc != NULL)
		idd.keyboardFunc(key, x, y);

}

/* Master Timer callback */
/* This is called as soon as possible from glut
 * with the value equal to that set by the calling function
 */
void iMasterTimer(int value) {
	int i;
  /* IMM_UPDATE_FRAME == frame update */
  if (value == IMM_UPDATE_FRAME) {

	/* Set the frame refresh command */
	igm.master.command[0]=IMM_UPDATE_FRAME;
	igm.master.command[1]=IMM_UPDATE_FRAME;

	/* Send to all of the nodes */
	iSendToAll(igm.master);

	/* Barrier to make sure all nodes get here at same time */
	MPI_Barrier(MPI_COMM_WORLD);

	/* Set the timer again for next time */
	glutTimerFunc(igg.fps_update,iMasterTimer,IMM_UPDATE_FRAME);

	/* Update the master display too */
	glutPostRedisplay();
  }

  /* IMM_UPDATE_WORLD == world update */
  if (value == IMM_UPDATE_WORLD) {

	igm.master.command[0] = IMM_UPDATE_WORLD;
	for (i=1; i<IMM_MSGSIZE; i++)
		igm.master.command[i] = 0;

	/* world update */
	if (idd.worldFunc != NULL)
		idd.worldFunc(igm.myrank, igm.ntasks, &igm.master);
	
	igm.master.command[0] = IMM_UPDATE_WORLD;
	
	iSendToAll(igm.master);

	/* Set the timer  for next time */
	glutTimerFunc(igg.world_update,iMasterTimer,IMM_UPDATE_WORLD);

  }
	/* Reset the message buffer */
	for (i=0; i<IMM_MSGSIZE; i++) {
		igm.slave.command[i]=0;
		igm.master.command[i]=0;
	}
}

void iDisplayFunc(void (*func)(void)) {
	/* Display callback */
	idd.displayFunc = func;
	glutDisplayFunc(func);
}

void iIdleFunc(void (*func)(void)) {
	idd.idleFunc = func;
}

void iReshapeFunc(void (*func)(int width, int height)) {
	idd.reshapeFunc = func;
}

void iKeyboardFunc(void (*func) (unsigned char key, int x, int y)) {
	idd.keyboardFunc = func;
}

void iSpecialFunc(void (*func) (int key, int x, int y)) {
	idd.specialFunc = func;
}

void iMouseFunc(void (*func) (int button, int state, int x, int y)) {
	idd.mouseFunc = func;
	glutMouseFunc(func);
}

void iMotionFunc(void (*func) (int x, int y)) {
	idd.motionFunc = func;
	glutMotionFunc(func);
}

void iPassiveMotionFunc(void (*func) (int x, int y)) {
	idd.passivemotionFunc = func;
	glutPassiveMotionFunc(func);
}

void iWorldFunc(void (*func) (int myrank, int ntasks, struct iMsg *cmd)) {
	idd.worldFunc = func;
}


/* Initialize display */

static void iInitDisplay( int numx, int numy, int numz, int nx, int ny, int nz) {

	if (idd.state >= IMM_STATE_DISPLAY) {
		printf("iInitDisplay already called!\n");
		exit(1);
	}
	if (idd.state != IMM_STATE_WORLD) {
		printf("iInitDisplay can't be called yet!\n");
		exit(1);
	}

	idd.numx = numx;
	idd.numy = numy;
	idd.numz = numz;
	idd.nx = nx;
	idd.ny = ny;
	idd.nz = nz;

	idd.aspectratio = numx / numy;

	idd.lookangle = 90;

	idd.eyex = 0;
	idd.eyey = 0;
	idd.eyez = 0;

	idd.upx = 0;
	idd.upy = 1;
	idd.upz = 0;

	idd.maxnumx = IMM_MAXNUMX;
	idd.realnumx = IMM_REALNUMX;
	idd.realnumy = IMM_REALNUMY;

	idd.theta = 180.0 / idd.maxnumx;
	idd.thetar = idd.theta * M_PI / 180.0;

	idd.rightoffset = ((180.0 / idd.theta) - (idd.realnumx )) / 2.0 ;

	iCalcLookat();

	idd.myx = 0;
/*	idd.myy = -.5;
	idd.myz = -3;
*/
	idd.myy = 0;
	idd.myz = -3;
	idd.myrx = 0;
	idd.myry = 0;
	idd.myrz = 0;
	

	/* iInitDisplay successful */
	idd.state = IMM_STATE_DISPLAY;
}

void iInitDisplayDefault() {

	int myrank, ntasks, numx, numy;
	int i;
	char name[10], num[2];
	int len;
/*
	MPI_Get_processor_name(name, &len);

	if (name[5] == '.') {
		num[0] = '0';
		num[1] = (char)name[4];
	} else if (name[0] == 'm') {
		num[0] = '0';
		num[1] = '0';
	} else {
		num[0] = (char)name[4];
		num[1] = (char)name[5];
	}

	if (iMyrank() > 0)
		i = atoi(num);
	else
		i = 0;
*/
        i=myrank=iMyrank();

        ntasks = iNtasks();
        numx = (int)IMM_REALNUMX;
        numy = (int)IMM_REALNUMY;

	i+=IMM_LEFTOFFSET;

	switch (i) {
		case 73:
	                iInitDisplay(numx, numy, 1, 21, 2, 0);
			break;
		case 72:
	                iInitDisplay(numx, numy, 1, 21, 3, 0);
			break;
		case 71:
	                iInitDisplay(numx, numy, 1, 21, 4, 0);
			break;
		case 70:
	                iInitDisplay(numx, numy, 1, 20, 2, 0);
			break;
		case 69:
	                iInitDisplay(numx, numy, 1, 20, 3, 0);
			break;
		case 68:
	                iInitDisplay(numx, numy, 1, 20, 4, 0);
			break;
		case 67:
	                iInitDisplay(numx, numy, 1, 19, 2, 0);
			break;
		case 66:
	                iInitDisplay(numx, numy, 1, 19, 3, 0);
			break;
		case 65:
	                iInitDisplay(numx, numy, 1, 19, 4, 0);
			break;
		case 64:
	                iInitDisplay(numx, numy, 1, 18, 2, 0);
			break;
		case 63:
	                iInitDisplay(numx, numy, 1, 18, 3, 0);
			break;
		case 62:
	                iInitDisplay(numx, numy, 1, 18, 4, 0);
			break;
		case 61:
	                iInitDisplay(numx, numy, 1, 17, 2, 0);
			break;
		case 60:
	                iInitDisplay(numx, numy, 1, 17, 3, 0);
			break;
		case 59:
	                iInitDisplay(numx, numy, 1, 17, 4, 0);
			break;
		case 58:
	                iInitDisplay(numx, numy, 1, 16, 2, 0);
			break;
		case 57:
	                iInitDisplay(numx, numy, 1, 16, 3, 0);
			break;
		case 56:
	                iInitDisplay(numx, numy, 1, 16, 4, 0);
			break;
		case 55:
	                iInitDisplay(numx, numy, 1, 15, 2, 0);
			break;
		case 54:
	                iInitDisplay(numx, numy, 1, 15, 3, 0);
			break;
		case 53:
	                iInitDisplay(numx, numy, 1, 15, 4, 0);
			break;
		case 52:
	                iInitDisplay(numx, numy, 1, 14, 2, 0);
			break;
		case 51:
	                iInitDisplay(numx, numy, 1, 14, 3, 0);
			break;
		case 50:
	                iInitDisplay(numx, numy, 1, 14, 4, 0);
			break;
		case 49:
	                iInitDisplay(numx, numy, 1, 13, 1, 0);
			break;
		case 48:
	                iInitDisplay(numx, numy, 1, 13, 2, 0);
			break;
		case 47:
	                iInitDisplay(numx, numy, 1, 13, 3, 0);
			break;
		case 46:
	                iInitDisplay(numx, numy, 1, 13, 4, 0);
			break;
		case 45:
	                iInitDisplay(numx, numy, 1, 13, 5, 0);
			break;
		case 44:
	                iInitDisplay(numx, numy, 1, 12, 1, 0);
			break;
		case 43:
	                iInitDisplay(numx, numy, 1, 12, 2, 0);
			break;
		case 42:
	                iInitDisplay(numx, numy, 1, 12, 3, 0);
			break;
		case 41:
	                iInitDisplay(numx, numy, 1, 12, 4, 0);
			break;
		case 40:
	                iInitDisplay(numx, numy, 1, 12, 5, 0);
			break;
		case 39:
	                iInitDisplay(numx, numy, 1, 11, 1, 0);
			break;
		case 38:
	                iInitDisplay(numx, numy, 1, 11, 2, 0);
			break;
		case 37:
	                iInitDisplay(numx, numy, 1, 11, 3, 0);
			break;
		case 36:
	                iInitDisplay(numx, numy, 1, 11, 4, 0);
			break;
		case 35:
	                iInitDisplay(numx, numy, 1, 11, 5, 0);
			break;
		case 34:
	                iInitDisplay(numx, numy, 1, 10, 1, 0);
			break;
		case 33:
	                iInitDisplay(numx, numy, 1, 10, 2, 0);
			break;
		case 32:
	                iInitDisplay(numx, numy, 1, 10, 3, 0);
			break;
		case 31:
	                iInitDisplay(numx, numy, 1, 10, 4, 0);
			break;
		case 30:
	                iInitDisplay(numx, numy, 1, 10, 5, 0);
			break;
		case 29:
	                iInitDisplay(numx, numy, 1, 9, 1, 0);
			break;
		case 28:
	                iInitDisplay(numx, numy, 1, 9, 2, 0);
			break;
		case 27:
	                iInitDisplay(numx, numy, 1, 9, 3, 0);
			break;
		case 26:
	                iInitDisplay(numx, numy, 1, 9, 4, 0);
			break;
		case 25:
	                iInitDisplay(numx, numy, 1, 9, 5, 0);
			break;
		case 24:
	                iInitDisplay(numx, numy, 1, 8, 2, 0);
			break;
		case 23:
	                iInitDisplay(numx, numy, 1, 8, 3, 0);
			break;
		case 22:
	                iInitDisplay(numx, numy, 1, 8, 4, 0);
			break;
		case 21:
	                iInitDisplay(numx, numy, 1, 7, 2, 0);
			break;
		case 20:
	                iInitDisplay(numx, numy, 1, 7, 3, 0);
			break;
		case 19:
	                iInitDisplay(numx, numy, 1, 7, 4, 0);
			break;
		case 18:
	                iInitDisplay(numx, numy, 1, 6, 2, 0);
			break;
		case 17:
	                iInitDisplay(numx, numy, 1, 6, 3, 0);
			break;
		case 16:
	                iInitDisplay(numx, numy, 1, 6, 4, 0);
			break;
		case 15:
	                iInitDisplay(numx, numy, 1, 5, 2, 0);
			break;
		case 14:
	                iInitDisplay(numx, numy, 1, 5, 3, 0);
			break;
		case 13:
	                iInitDisplay(numx, numy, 1, 5, 4, 0);
			break;
		case 12:
	                iInitDisplay(numx, numy, 1, 4, 2, 0);
			break;
		case 11:
	                iInitDisplay(numx, numy, 1, 4, 3, 0);
			break;
		case 10:
	                iInitDisplay(numx, numy, 1, 4, 4, 0);
			break;
		case 9:
	                iInitDisplay(numx, numy, 1, 3, 2, 0);
			break;
		case 8:
	                iInitDisplay(numx, numy, 1, 3, 3, 0);
			break;
		case 7:
	                iInitDisplay(numx, numy, 1, 3, 4, 0);
			break;
		case 6:
	                iInitDisplay(numx, numy, 1, 2, 2, 0);
			break;
		case 5:
	                iInitDisplay(numx, numy, 1, 2, 3, 0);
			break;
		case 4:
	                iInitDisplay(numx, numy, 1, 2, 4, 0);
			break;
		case 3:
	                iInitDisplay(numx, numy, 1, 1, 2, 0);
			break;
		case 2:
	                iInitDisplay(numx, numy, 1, 1, 3, 0);
			break;
		case 1:
	                iInitDisplay(numx, numy, 1, 1, 4, 0);
			break;
		case 0:
	                iInitDisplay(numx, numy, 1, 0, 0, 0);
			break;
			break;

		default:
	                iInitDisplay(numx, numy, 1, numx/numy, 0, 0);
			break;
	}
}

/* Initialize world variables */
void iInitWorld(	float xmax, float xmin, 
			float ymax, float ymin, 
			float zmax, float zmin, 
			int fps_update, int world_update, int mode
		  )
{

	if (idd.state >= IMM_STATE_WORLD) {
		printf("iInitWorld already called!\n");
		exit(1);
	}
	if (idd.state != IMM_STATE_INIT) {
		printf("iInitWorld can't be called yet!\n");
		exit(1);
	}

	if (mode < IMM_MODE_2D || mode > IMM_MODE_3D_FLAT) {
		printf("iInitWorld: invalid or unsupported mode!\n");
		exit(1);
	}

	idd.iMode = mode;

	if (mode == IMM_MODE_3D_PERSPECTIVE) {
		idd.fovx = xmax;
	}
	
	idd.xmax = xmax;
	idd.xmin = xmin;
	idd.ymax = ymax; 
	idd.ymin = ymin; 
	idd.zmax = zmax;
	idd.zmin = zmin;

	idd.xr = idd.xmax - idd.xmin;
	idd.yr = idd.ymax - idd.ymin;
	idd.zr = idd.zmax - idd.zmin;

	/* set our attempted frame and world update (in milliseconds) */
	
	igg.fps_update 	= fps_update;
	igg.world_update = world_update;

	if (igg.fps_update == 0) 
		igg.fps_update = 10;
	if (igg.world_update == 0)
		igg.world_update = 20;


	/* iInitWorld successful */
	idd.state = IMM_STATE_WORLD;
}

void iInitWindowSize(int width, int height) {

	if (igm.myrank == 0) {
	
		igg.windH = height;
		igg.windW = width;

		glutReshapeWindow(igg.windW, igg.windH);	
	}
}

void iInitWindowPosition(int x, int y) {

	if (igm.myrank == 0) {
	
		glutPositionWindow(x,y);	
	}
}

/* Main function! */
int iInit(int *argc, char **argv)
{
	int i;
	if (idd.state >= IMM_STATE_INIT && idd.state <= IMM_STATE_GO) {
		printf("iInit already called!\n");
		exit(1);
	}

	/* Initialize message buffer */
	for (i=0; i<IMM_MSGSIZE; i++) {
		igm.slave.command[i]=0;
		igm.master.command[i]=0;
	}
	idd.displayFunc = NULL;
	idd.idleFunc = NULL;
	idd.keyboardFunc = NULL;
	idd.specialFunc = NULL;
	idd.mouseFunc = NULL;
	idd.worldFunc = NULL;
	idd.reshapeFunc = NULL;

	ic_read_config();

	/* MPI Init functions, get number of tasks and my rank */
	MPI_Init(argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &igm.ntasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &igm.myrank);
	
	/* Be nice and introduce yourself */
/*	printf("Hello,  I am node%i.\n",igm.myrank);
*/
	/* Glut Initialization */
	glutInit(argc, argv);

	/* Process command line arguments */
	if (iArgs(argc, argv) == GL_FALSE) {
		exit(1);
	}

	/* Glut window creation */
	igg.windH = 100;
	igg.windW = (int) (igg.windH*(igm.ntasks-1)/4.0);
	igg.windW = (int) (igg.windW * .75);

	if (igg.windW >=800)
		igg.windW = 800;

	glutInitWindowPosition(0, 0); 

	if (igm.myrank == 0)
		glutInitWindowSize( igg.windW, igg.windH);
	else
		glutInitWindowSize( 400, 400);

	igg.windType = GLUT_RGBA;
	igg.windType |= (igg.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
	igg.windType |= GLUT_DEPTH;

	glutInitDisplayMode(igg.windType);

	if (glutCreateWindow("MPI OPENGL!") == GL_FALSE) {
		exit(1);
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* initialize isWaiting so it will check for messages first */
	igm.isWaiting=0;

	/* Window reshape callback */
	glutReshapeFunc(iReshape);

	/* If not the master (if slave) */
	if (igm.myrank != 0) {

		/* Set the slave idle callback*/
		glutIdleFunc(iIdle);

		/* Make it full screen */
		glutFullScreen();

	} else {

		/* Only master gets here */

		/* Keyboard callback */
		glutKeyboardFunc(iMasterKey);

		/* Special Key callback */
		glutSpecialFunc(iMasterSpecialKey);

		/* Call masterTimer every fps_update ms with value == 1 */
		glutTimerFunc(igg.fps_update,iMasterTimer,IMM_UPDATE_FRAME);
		glutTimerFunc(igg.world_update,iMasterTimer,IMM_UPDATE_WORLD);
	
	}


	/* iInit successful */
	idd.state = IMM_STATE_INIT;
}

void iMainLoop(void) {

	if (idd.state >= IMM_STATE_GO) {
		printf("iMainLoop already called!\n");
		exit(1);
	}
	if (idd.state != IMM_STATE_DISPLAY) {
		printf("iMainLoop can't be called yet!\n");
		exit(1);
	}

	/* iMainLoop successful */
	idd.state = IMM_STATE_GO;

	/* will never return */
	glutMainLoop();
}

#ifdef __cplusplus
}
#endif

#endif

