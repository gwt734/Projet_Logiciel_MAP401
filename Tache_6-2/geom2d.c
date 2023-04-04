#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "geom2d.h"

Point set_point(double x,double y)
{
Point P={x,y};
return P;
}

Vecteur set_vect(double x, double y)
{
Vecteur V = {x, y};
return V;
}

Vecteur add_vect(Vecteur V1,Vecteur V2)
{
return set_vect(V1.x+V2.x,V1.y+V2.y);
}

Point add_point(Point P1, Point P2)
{
return set_point(P1.x + P2.x, P1.y + P2.y);
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

Point mult_scalaire_point (Point A, double k)
{
    A.x = A.x * k;
    A.y = A.y * k;
    return A;
}

double distance_points(Point A, Point B)
{
    return norme_vect(vect_bipoint(A,B));
}

double produit_scalaire(Vecteur V1, Vecteur V2)
{
    return V1.x*V2.x + V1.y*V2.y;
}

double angle_vect(Vecteur V1, Vecteur V2)
{
    return acos(produit_scalaire(V1,V2)/(norme_vect(V1)*norme_vect(V2)));
}

Vecteur vect_unitaire(Vecteur V)
{
    return mult_scalaire(V,1/norme_vect(V));
}

Vecteur vect_normal(Vecteur V)
{
    return set_vect(-V.y,V.x);
}

Vecteur rotation(Vecteur V, double angle)
{
    double x = V.x*cos(angle) - V.y*sin(angle);
    double y = V.x*sin(angle) + V.y*cos(angle);
    return set_vect(x,y);
}

bool est_egal_points(Point A, Point B)
{
    return (A.x == B.x && A.y == B.y);
}

double distance_point_segment(Point P, Point A, Point B)
{
    if (est_egal_points(A, B))
    {
        return distance_points(P, A);
    }
    Vecteur AB = vect_bipoint(A, B);
    Vecteur AP = vect_bipoint(A, P);

    double l = (produit_scalaire(AB, AP)) / produit_scalaire(AB, AB);
    if (l < 0)
    {
        return distance_points(P, A);
    }
    else if (l > 1)
    {
        return distance_points(P, B);
    }
    else
    {
        Point Q = add_point(A, mult_scalaire_point(add_point(B, mult_scalaire_point(A, -1)), l));
        return distance_points(P, Q);
    }
}