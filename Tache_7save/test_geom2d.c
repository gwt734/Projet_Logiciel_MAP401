#include <stdio.h>
#include "geom2d.h"

int main(int argc,char** argv)
{
    /*
Point A,B,C;
Vecteur U, V;
A=set_point(1.0,-3.0);
B=set_point(4.0,1.0);
C=add_point(A,B); -->C=(5.0,−2.0)
U=vect_bipoint(C,A); //-->U=(−4.0,−1.0)

double n=norme_vect(U);
V = mult_scalaire(U, 12.37);
double d = distance_points(A,B);
printf(" C = (%f,%f)\n U = (%f,%f)\n n = %f\n V = (%f,%f)\n d = %f\n", C.x,C.y, U.x,U.y, n, V.x, V.y, d);
*/

Point C0 = {0, 2};
Point C1 = {9, 5};
Point C2 = {6,8};
Bezier2 B0;
B0.C0 = C0;
B0.C1 = C1;
B0.C2 = C2;

Bezier3 B1 = conversion_Bezier2_vers_Bezier3(B0);
//Bezier3 B2 = conversion_Bezier2_vers_Bezier3_2(B0);
printf("%f.0, %f.0, %f.0, %f.0, %f.0, %f.0, %f.0, %f.0\n", B1.C0.x , B1.C0.y, B1.C1.x, B1.C1.y, B1.C2.x, B1.C2.y, B1.C3.x, B1.C3.y);
//printf("%f.0, %f.0, %f.0, %f.0, %f.0, %f.0, %f.0, %f.0\n", B2.C0.x , B2.C0.y, B2.C1.x, B2.C1.y, B2.C2.x, B2.C2.y, B2.C3.x, B2.C3.y);
printf("%f , %f , %f , %f\n", calcul_point_bezier3(B1, 0.5).x, calcul_point_bezier3(B1, 0.5).y, calcul_point_bezier2(B0, 0.5).x, calcul_point_bezier2(B0, 0.5).y);

return 0;
}



