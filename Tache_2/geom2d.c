#include <stdlib.h>
#include <math.h>
#include "geom2d.h"

Point set_point(double x,double y)
{
Point P={x,y};
return P;
}

Point add_point(Point P1,Point P2)
{
return set_point(P1.x+P2.x,P1.y+P2.y);
}

Vecteur vect_bipoint(Point A,Point B)
{
Vecteur V={B.x-A.x,B.y-A.y};
return V;
}

double norme_vect(Vecteur V)
{
    return sqrt(V.x*V.x + V.y*V.y);
}

Vecteur mult_scalaire (Vecteur V, double a)
{
    V.x = V.x * a;
    V.y = V.y * a;
    return V;
}

double distance_points(Point A, Point B)
{
    return norme_vect(vect_bipoint(A,B));
}