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

Point avancer(Point pos, Orientation o);

Orientation tourner(Orientation o, bool vers_la_droite);

Point trouver_pixel_depart(Image I);

Pixel get_pixel_relatif(Image I, Point p, Orientation o, Direction d);

Orientation nouvelle_orientation(Image I, Point pos, Orientation o);

Liste_Point calcul_contour(Image I, Point p_depart);

#endif
