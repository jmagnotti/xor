#ifndef __IMMERGE_H_
#define __IMMERGE_H_ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <mpi.h>

#ifdef __cplusplus
extern "C" {
#endif


#define MSGTAG 1
#define SYNCTAG 2
#define IMM_MSGSIZE 4096 

#define IMM_MOVE_D		.1

#define IMM_SHUTDOWN 		1
#define IMM_REFRESH 		2
#define IMM_UPDATE_WORLD 	50
#define IMM_UPDATE_FRAME	99

#define IMM_STATE_NOINIT	1
#define IMM_STATE_INIT		2
#define IMM_STATE_WORLD		3
#define IMM_STATE_DISPLAY	4
#define IMM_STATE_GO		5

#define IMM_MODE_2D		1
#define IMM_MODE_2D_SHRINK	2
#define IMM_MODE_2D_WINDOW	3
#define IMM_MODE_3D		4
#define IMM_MODE_3D_WRAP	4
#define IMM_MODE_3D_PERSPECTIVE	5
#define IMM_MODE_3D_FLAT	6
#define IMM_MODE_3D_ORTH	7

struct iMsg {
	float command[IMM_MSGSIZE];
};
struct iData {
	void (*displayFunc) 	(void);
	void (*idleFunc) 	(void);
	void (*keyboardFunc) 	(unsigned char key, int x, int y);
	void (*specialFunc)  	(int key, int x, int y);
	void (*mouseFunc)	(int button, int state, int x, int y);
	void (*motionFunc) 	(int x, int y);
	void (*passivemotionFunc) 	(int x, int y);
	void (*reshapeFunc)	(int width, int height);

	void (*worldFunc) 	(int myrank, int ntasks, struct iMsg *cmd);

	float xmax;
	float xmin;
	float ymax;
	float ymin;
	float zmax;
	float zmin;

	float myxmax;	
	float myxmin;
	float myymax;	
	float myymin;
	float myzmax;	
	float myzmin;

	float myx, myy, myz;
	float myrx, myry, myrz;

	float theta, rad_theta;
	float xcenter,ycenter,zcenter;
	float rightoffset;
	float maxnumx, realnumx, realnumy;

	float eyex, eyey, eyez;
	float lookatx, lookaty, lookatz;
	float beyex, beyey, beyez;
	float blookatx, blookaty, blookatz;
	float upx, upy, upz;
	float lookangle;

	float fovx, fovy;
	float myfovx, myfovy;

	float myxr, myyr, myzr;
	float myxoffset, myyoffset, myzoffset;
	float xr, yr, zr;	  /* x,y,z ranges... =(*max - *min) */
	float numx, numy, numz;   /* number of monitors in x,y,z    */
	float nx, ny, nz;	  /* this node's mon. num in x,y,z  */

	float aspectratio;

	int iMode;

	int state;
};

struct igGlut {
		/* Global GL information */
	GLenum doubleBuffer, windType;
	GLint windW, windH;
	int fps_update;
	int world_update;
};

struct igMpi {
		/* Global MPI information */
	MPI_Request slaverequest;
	MPI_Status slavestatus;

	int isWaiting;
	int myrank;
	int ntasks;
	
	struct iMsg slave;
	struct iMsg master;

	MPI_Request masterrequest[100];
	MPI_Status  masterstatus[100];
};

/* Shutdown and exit */
static void do_shutdown(void); 

/* Send some command to all nodes and wait for them to receive it */
int iSendToAll(struct iMsg cmd);

int iSendToMaster(struct iMsg cmd);

void iCalcLookat();

/* Window reshape calls this */
static void iReshape(int width, int height);

int iMyrank();

int iNtasks();

int iXrank();

int iYrank();

/* Process command line arguments */
static GLenum iArgs(int *argc, char **argv);

/* slave node idle function. */
/* This is called as much as possible from Glut.
 * Calls Asynconous mpi receive and then tests until 
 * a message is received.  When it is, process it.
 */

void iIdle(void);

/* Master special key callback */
static void iMasterSpecialKey(int key, int x, int y);


/* Master key callback */
/* Main controller of nodes...
 * When a key is pressed, this function is called
 * and it is processed to change variables as appropriate
 * and notify nodes as appropriate
 */
static void iMasterKey(unsigned char key, int x, int y);


/* Master Timer callback */
/* This is called as soon as possible from glut
 * with the value equal to that set by the calling function
 */
void iMasterTimer(int value);

void iDisplayFunc(void (*func)(void));

void iIdleFunc(void (*func)(void));

void iReshapeFunc(void (*func)(int width, int height));

void iKeyboardFunc(void (*func) (unsigned char key, int x, int y));

void iSpecialFunc(void (*func) (int key, int x, int y));

void iMouseFunc(void (*func) (int button, int state, int x, int y));

void iMotionFunc(void (*func) (int x, int y));

void iPassiveMotionFunc(void (*func) (int x, int y));

void iWorldFunc(void (*func) (int myrank, int ntasks, struct iMsg *cmd));


/* Initialize display */

static void iInitDisplay( int numx, int numy, int numz, int nx, int ny, int nz);

void iInitWindowSize(int width, int height);

void iInitDisplayDefault();

/* Initialize world variables */
void iInitWorld(	float xmax, float xmin, 
			float ymax, float ymin, 
			float zmax, float zmin, 
			int fps_update, int world_update, int mode
		  );


void iInitWindowPosition(int x, int y);

/* Main function! */
int iInit(int *argc, char **argv);

void iMainLoop(void);


#ifdef __cplusplus
}
#endif

#endif

