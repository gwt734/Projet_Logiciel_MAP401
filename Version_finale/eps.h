#ifndef EPS_H
#define EPS_H

#include "liste_point.h"

typedef enum
{
    STROKE,
    FILL
} Type_dessin;

/*
 * Fonction qui écrit un fichier eps à partir d'une liste de contours
 * Elle dessine le contour comme une suite de segments
 * Entrée :
 *  - LC : liste de contours
 *  - largeur : largeur de l'image
 *  - hauteur : hauteur de l'image
 *  - nom_fichier : nom du fichier eps
 *  - type_dessin : type de dessin (STROKE ou FILL)
 */
void ecrire_fichier_eps(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin);

/*
 * Fonction qui écrit un fichier eps à partir d'une liste de contours
 * Elle dessine le contour comme une suite de courbes de Bézier de degré 2
 * Entrée :
 *  - LC : liste de contours
 *  - largeur : largeur de l'image
 *  - hauteur : hauteur de l'image
 *  - nom_fichier : nom du fichier eps
 *  - type_dessin : type de dessin (STROKE ou FILL)
 */
void ecrire_fichier_eps_bezier2(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin);

/*
 * Fonction qui écrit un fichier eps à partir d'une liste de contours
 * Elle dessine le contour comme une suite de courbes de Bézier de degré 3
 * Entrée :
 *  - LC : liste de contours
 *  - largeur : largeur de l'image
 *  - hauteur : hauteur de l'image
 *  - nom_fichier : nom du fichier eps
 *  - type_dessin : type de dessin (STROKE ou FILL)
 */
void ecrire_fichier_eps_bezier3(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin);

#endif
