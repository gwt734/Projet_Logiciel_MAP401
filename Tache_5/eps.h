#ifndef EPS_H
#define EPS_H

#include "liste_point.h"

typedef enum
{
    STROKE,
    FILL
} Type_dessin;

void ecrire_fichier_eps(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin);

#endif
