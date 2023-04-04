#include <stdio.h>
#include "geom2d.h"

int main(int argc,char** argv)
{
Point A,B,C;
Vecteur U, V;
A=set_point(1.0,-3.0);
B=set_point(4.0,1.0);
C=add_point(A,B); /*-->C=(5.0,−2.0)*/
U=vect_bipoint(C,A); /*-->U=(−4.0,−1.0)*/
double n=norme_vect(U);
V = mult_scalaire(U, 12.37);
double d = distance_points(A,B);
printf(" C = (%f,%f)\n U = (%f,%f)\n n = %f\n V = (%f,%f)\n d = %f\n", C.x,C.y, U.x,U.y, n, V.x, V.y, d);
}