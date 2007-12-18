/*

    Quadratic Picard Solver for the initial value ordinary differential
    equation system (IVODES):

       y' = F(y)  ;  y(0) = y_0  ;  y in R^n, F a quadratic polynomial

    see qpicard.h for the details on IVODES.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qpicard.h"

int main()
{

   double h, tyme, r;
   double bcsum,dsum,sum1,sum2,sum22,sum3,sum32,sum33,temp,temp1;

   double grav,mu,len,mass,phi,omega,Amp;
   int i,j,k,n,m,ns,num_time_steps;

   FILE *fp1,*fp2;

/* Open the file for the numerical data. */

   fp1 = fopen("ThetaValues", "w");

/* Zero out all the coefficients. */

   for (i=1; i<=ne; i++) 
   {

      a[i] = 0;

   }
   for (i=1; i<=ne; i++) 
   {
   for (j=1; j<=ne; j++) 
   {

     b[i][j] = 0;
     c[i][j] = 0;
     
   }
   }
   for (i=1; i<=ne; i++) 
   {
   for (j=1; j<=ne; j++) 
   {
   for (k=1; k<=ne; k++) 
   {

     d[i][j][k] = 0;

   }
   }
   }

/* Set up the coefficients in your equation. */

   

   grav = 10;

   mu = 0.2;

   len = 10;

   mass = 1;

   

   phi = 0;

   omega = 1;

	Amp = 1.;


   b[1][2] = 1.0;

   b[2][2] = -mu/mass;

   b[2][3] = -grav/len;

   d[3][2][4] = 1.0;

   d[4][2][3] = -1.0;

   b[5][6] = -omega;

   b[6][5] = omega;

/* Give the initial conditions which are also the zeroth coefficients in
   the Maclaurin solutions. */

   alpha[1][0] = atan(1.0);
   alpha[2][0] = 0.0;
   alpha[3][0] = cos(alpha[1][0]);

   alpha[4][0] = sin(alpha[1][0]);

   alpha[5][0] = Amp*cos(phi);

   alpha[6][0] = -Amp*sin(phi);
      
   printf("  %28.16lf ",alpha[1][0]); 
   printf("  %28.16lf ",alpha[2][0]); 

/* h is the local time step */
      
   h = pow(1/2.,6.);
      
   printf("   %8.16e \n",h);
  fprintf(fp1,"   %8.16e \n",alpha[1][0]);

/* tyme is the global time step */

   tyme = pow(2.,11.)*h;

/* num_time_steps is the number of iterations in the global time step */

   num_time_steps = ceil(tyme/h);

/* The algorithm for generating the Maclaurin solutions is here. */

   for (ns=1; ns<=num_time_steps; ns++) 
   {

     for (i=1; i<=ne; i++) 
     {

/* calculate the first derivative Maclaurin coefficient of each function
   in the solution. */

       alpha[i][1] = a[i];
       bcsum = 0;
       for (m=1; m<=ne; m++) 
       {

         bcsum = bcsum + b[i][m]*alpha[m][0]+c[i][m]*alpha[m][0]*alpha[m][0];

       }
       dsum = 0;
       for (m=1; m<=ne; m++)
       {

         for (n=m+1; n<=ne; n++)
         {

           dsum = dsum + d[i][m][n]*alpha[m][0]*alpha[n][0];

         }
   
       }
/* This is the first derivative coefficient of the Maclaurin solutions. */

       alpha[i][1] = alpha[i][1]+bcsum+dsum;

     }

/* Now calculate the rest of the Maclaurin coefficients for each function. */

     for (k=2; k<=nd; k++)
     {

       for (i=1; i<=ne; i++)
       {

         sum1 = 0;
         for (j=1; j<=ne; j++)
         {

            sum1 = sum1 + b[i][j]*alpha[j][k-1];

         }
         sum2 = 0;
         for (j=1; j<=ne; j++)
         {

            sum22 = 0;
            for (m=0; m<=k-1; m++)
            {

              sum22 = sum22+alpha[j][m]*alpha[j][k-m-1];

            }
            sum2 = sum2 + c[i][j]*sum22;

          }  
          sum3 = 0;
          for (m=1; m<=ne; m++)
          {

            sum32 = 0;
            for (j=m+1; j<=ne; j++)
            {

              sum33 = 0;
              for (n=0; n<=k-1; n++)
              {

                sum33 = sum33 + alpha[m][n]*alpha[j][k-n-1];

              }
              sum32 = sum32 + d[i][m][j]*sum33;

            }
            sum3 = sum3 + sum32;

          }

/* These are the Maclaurin coefficients. */

          alpha[i][k] = (sum1+sum2+sum3)/k;

        }

      } 

/* Now use the Maclaurin coefficients to evaluate the Maclaurin polynomials. */

      for (i=1; i<=ne; i++)
      {

        temp = alpha[i][nd-1] + alpha[i][nd]*h;       
        for (j=1; j<=nd-1; j++)
        {
  
          temp = h*temp+alpha[i][nd-j-1];

        }
        temp1 = alpha[1][0];

/* This is the value of the Maclaurin polynomial at the next time step and
   is also the constant term in the next Maclaurin polynomial for the next
   time step. */

        alpha[i][0] = temp; 

     }      
    fprintf(fp1,"   %8.16e \n",alpha[1][0]);
   }  

   for (i=1; i<=ne; i++)
   {

     printf(" \n");
      
     printf("  %8.16lf ",temp1);

     for (j=1; j<=nd; j++)
     {
 
       printf(" + %8.16lf *t^%d",alpha[i][j],j);

     }

   }

   printf(" \n");

  fclose(fp1);
  fclose(fp2);
  return 0;

} 
