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

double distance_points(Point A, Point B);