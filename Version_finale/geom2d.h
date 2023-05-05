#ifndef GEOM2D_H
#define GEOM2D_H

#include <stdbool.h>

#define PRECISION_EGALITE 0.0001

typedef struct Vecteur
{
    double x, y; /*coordonnees*/
} Vecteur;
typedef struct Point
{
    double x, y; /*coordonnees*/
} Point;

typedef struct Bezier2
{
    Point C0, C1, C2;
} Bezier2;

typedef struct Bezier3
{
    Point C0, C1, C2, C3;
} Bezier3;

/*cree le point de coordonnées(x,y)*/
Point set_point(double x, double y);

/*cree le vecteur de coordonnées(x,y)*/
Vecteur set_vect(double x, double y);

/*somme V1+V2*/
Vecteur add_vect(Vecteur V1, Vecteur V2);

/*somme P1+P2*/
Point add_point(Point P1, Point P2);

/*vecteur correspondant au bipoint−→AB*/
Vecteur vect_bipoint(Point A, Point B);

double norme_vect(Vecteur V);

Vecteur mult_scalaire(Vecteur V, double a);

Point mult_scalaire_point(Point A, double k);

double distance_points(Point A, Point B);

double produit_scalaire(Vecteur V1, Vecteur V2);

double angle_vect(Vecteur V1, Vecteur V2);

Vecteur vect_unitaire(Vecteur V);

Vecteur vect_normal(Vecteur V);

Vecteur rotation(Vecteur V, double angle);

bool est_egal_points(Point A, Point B);

bool est_environ_egal_points(Point P1, Point P2);

double distance_point_segment(Point P, Point A, Point B);

double distance_point_bezier2(Point P, Bezier2 B, double ti);

double distance_point_bezier3(Point P, Bezier3 B, double ti);

Point calcul_point_bezier2(Bezier2 B, double t); // 0<=t<=1

Point calcul_point_bezier3(Bezier3 B, double t); // 0<=t<=1

Bezier3 conversion_Bezier2_vers_Bezier3(Bezier2 B);

#endif