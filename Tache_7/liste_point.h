#ifndef LISTE_POINT_H
#define LISTE_POINT_H

#include "geom2d.h"

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
    Point data;                        /* donn�e de l'�l�ment de liste */
    struct Cellule_Liste_Point_ *suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Point;

/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
    unsigned int taille;        /* nombre d'�l�ments dans la liste */
    Cellule_Liste_Point *first; /* pointeur sur le premier �l�ment de la liste */
    Cellule_Liste_Point *last;  /* pointeur sur le dernier �l�ment de la liste */
                                /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type cellule de liste de Contour ----*/
typedef struct Cellule_Liste_Contour_
{
    Contour data;                        /* donn�e de l'�l�ment de liste */
    struct Cellule_Liste_Contour_ *suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Contour;

/*---- le type liste de Contour ----*/
typedef struct Liste_Contour_
{
    unsigned int taille;          /* nombre d'�l�ments dans la liste */
    Cellule_Liste_Contour *first; /* pointeur sur le premier �l�ment de la liste */
    Cellule_Liste_Contour *last;  /* pointeur sur le dernier �l�ment de la liste */
                                  /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour;

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
    unsigned int taille; /* nombre d'�l�ments dans le tableau */
    Point *tab;          /* (pointeur vers) le tableau des �l�ments */
} Tableau_Point;

/*---- le type tableau de point ----*/
typedef struct Tableau_Contour_
{
    unsigned int taille; /* nombre d'�l�ments dans le tableau */
    Contour *tab;        /* (pointeur vers) le tableau des �l�ments */
} Tableau_Contour;

/*---- les prototypes des fonctions ----*/

/*
 * Crée un élément de liste de point
 *
 * v: le point à stocker dans l'élément de liste
 *
 * retourne: un pointeur sur l'élément de liste créé
 */
Cellule_Liste_Point *creer_element_liste_Point(Point v);

/*
 * Crée une liste de points vide
 *
 * retourne: une liste de points vide
 */
Liste_Point creer_liste_Point_vide();

/*
 * Ajoute un élément à la fin d'une liste de points
 *
 * L: la liste de points à laquelle on veut ajouter un élément
 * e: le point à ajouter à la liste
 *
 * retourne: la liste de points avec l'élément ajouté
 */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e);

/*
 * Supprime un élément de la liste de point
 *
 * L: la liste de points à laquelle on veut supprimer un élément
 * e: le point à supprimer de la liste
 *
 * retourne: la liste de points avec l'élément supprimé
 */
Liste_Point supprimer_liste_Point(Liste_Point L);

/*
 * Concatène deux listes de points
 *
 * L1: la première liste de points
 * L2: la deuxième liste de points
 *
 * retourne: la liste de points résultant de la concaténation
 */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

/*
 * Convertit une liste de points en tableau de points
 *
 * L: la liste de points à convertir
 *
 * retourne: le tableau de points résultant de la conversion
 */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

/*
 * Affiche le contour dans la console
 *
 * L: le contour à afficher
 */
void ecrire_contour(Liste_Point L);

/*
 * Ecrit le contour dans le fichier donné
 *
 * L: le contour à afficher
 * nom_fichier: le nom du fichier
 */
void ecrire_contour_fichier(Liste_Point L, char *nom_fichier);

Cellule_Liste_Contour *creer_element_liste_Contour(Liste_Point v);

/*
 * Crée une liste de contours vide
 *
 * retourne: une liste de contours vide
 */
Liste_Contour creer_liste_Contour(void);

/*
 * Ajoute un élément à la fin d'une liste de contours
 *
 * L: la liste de contours à laquelle on veut ajouter un élément
 * c: le contour à ajouter à la liste
 *
 * retourne: la liste de contours avec l'élément ajouté
 */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Liste_Point c);

/*
 * Concatène les deux listes de contours
 *
 * L1: la première liste de contours
 * L2: la deuxième liste de contours
 *
 * retourne: la liste de points résultant de la concaténation
 */
Liste_Contour concatener_liste_Contour(Liste_Contour L1, Liste_Contour L2);

void ecrire_contours_fichier(Liste_Contour L, char *nom_fichier);

#endif