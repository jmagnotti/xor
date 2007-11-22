/*

   qpicard.h

   This is the header file for defining the IVODES that will
   be solved using the quadratic picard method.

   ne - Number of equations in the IVODES
   nd - Degree of the Maclaurin polynomials to approximate the solutions
        to the IVODES

   a - the constant terms in the IVODES
   b - the linear term coefficients in the IVODES
   c - the squared term coefficients in the IVODES
   d - the mixed term coefficients in the IVODES
   
   alpha - the coefficients in the Maclaurin polynomial approximations

   The IVODES is

   y_i' = a_i + Sum( b_i,j y_j, j=1,...,ne) + Sum( c_i,j y_j^2, j=1,...,ne) + 
          Sum( d_i,j,k y_j y_k, j=1,...,ne), k = j+1,...,ne)  i = 1,...,ne

*/

#define ne 6
#define nd 8

double a[ne+1],b[ne+1][ne+1],c[ne+1][ne+1],d[ne+1][ne+1][ne+1],alpha[ne+1][nd+1];
