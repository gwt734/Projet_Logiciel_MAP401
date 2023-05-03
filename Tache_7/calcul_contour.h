#ifndef CALCUL_CONTOURS_H
#define CALCUL_CONTOURS_H

#include "image.h"
#include "geom2d.h"
#include "liste_point.h"
#include <stdbool.h>

typedef enum
{
    Nord,
    Est,
    Sud,
    Ouest
} Orientation;

typedef enum
{
    Avant_gauche,
    Avant_droit,
    Arriere_gauche,
    Arriere_droit
} Direction;

/*
 * Avance d'une case dans la direction de l'orientation
 *
 * pos: position de départ
 * o: orientation
 *
 * retourne: la nouvelle position
 */
Point avancer(Point pos, Orientation o);

/*
 * Tourne à droite ou à gauche
 *
 * o: orientation de départ
 * vers_la_droite: true pour tourner à droite, false pour tourner à gauche
 *
 * retourne: la nouvelle orientation
 */
Orientation tourner(Orientation o, bool vers_la_droite);

/*
 * Trouve un pixel de départ (un pixel noir qui est sous un pixel blanc)
 *
 * I: image
 *
 * retourne: le point de départ
 */
Point trouver_pixel_depart(Image I);

/*
 * Trouve le pixel se trouvant à la direction donnée relativement à la position et l'orientation
 *
 * I: image
 * p: position
 * o: orientation
 * d: direction
 *
 * retourne: la valeur du pixel
 */
Pixel get_pixel_relatif(Image I, Point p, Orientation o, Direction d);

/*
 * Calcule l'orientation après avoir passé ce pixel en fonction de la direction et de l'orientation
 *
 * I: image
 * pos: position
 * o: orientation
 *
 * retourne: la nouvelle orientation
 */
Orientation nouvelle_orientation(Image I, Point pos, Orientation o);

/*
 * Calcule le contour d'une image
 *
 * I: image
 *
 * retourne: la liste des points du contour
 */
Liste_Contour calcul_contour(Image I);

#endif
