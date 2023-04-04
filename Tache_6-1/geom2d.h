#ifndef GEOM2D_H
#define GEOM2D_H

#include <stdbool.h>

typedef struct Vecteur{
double x,y;/*coordonnees*/
}Vecteur;
typedef struct Point{
double x,y;/*coordonnees*/
}Point;

/*cree le point de coordonnées(x,y)*/
Point set_point(double x,double y);

/*somme P1+P2*/
Point add_point(Point P1,Point P2);

/*vecteur correspondant au bipoint−→AB*/
Vecteur vect_bipoint(Point A,Point B);

double norme_vect(Vecteur V);

Vecteur mult_scalaire (Vecteur V, double a);

Point mult_scalaire_point(Point A, double k);

double distance_points(Point A, Point B);

double produit_scalaire(Vecteur V1, Vecteur V2);

double angle_vect(Vecteur V1, Vecteur V2);

Vecteur vect_unitaire(Vecteur V);

Vecteur vect_normal(Vecteur V);

Vecteur rotation(Vecteur V, double angle);

bool est_egal_points(Point A, Point B);

double distance_point_segment(Point P, Point A, Point B);

#endif