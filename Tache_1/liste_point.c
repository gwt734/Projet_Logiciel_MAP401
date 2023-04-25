#include <stdlib.h>
#include <stdio.h>
#include "liste_point.h"
#include "geom2d.h"

/* cr�er une cellule de liste avec l'�l�ment v
   renvoie le pointeur sur la cellule de liste cr��e
   la fonction s'arrete si la cr�ation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
    Cellule_Liste_Point *el;
    el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
    if (el == NULL)
    {
        fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}
/* cr�er une liste vide */
Liste_Point creer_liste_Point_vide()
{
    Liste_Point L = {0, NULL, NULL};
    return L;
}

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
    Cellule_Liste_Point *el;

    el = creer_element_liste_Point(e);
    if (L.taille == 0)
    {
        /* premier �l�ment de la liste */
        L.first = L.last = el;
    }
    else
    {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
    Cellule_Liste_Point *el = L.first;

    while (el)
    {
        Cellule_Liste_Point *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
    /* cas o� l'une des deux listes est vide */
    if (L1.taille == 0)
        return L2;
    if (L2.taille == 0)
        return L1;

    /* les deux listes sont non vides */
    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
    L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
    L1.taille += L2.taille;   /* nouvelle taille pour L1 */
    return L1;
}
/* cr�er une s�quence de points sous forme d'un tableau de points
   � partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
    Tableau_Point T;

    /* taille de T = taille de L */
    T.taille = L.taille;

    /* allocation dynamique du tableau de Point */
    T.tab = malloc(sizeof(Point) * T.taille);
    if (T.tab == NULL)
    {
        /* allocation impossible : arret du programme avec un message */
        fprintf(stderr, "sequence_points_liste_vers_tableau : ");
        fprintf(stderr, " allocation impossible\n");
        exit(-1);
    }

    /* remplir le tableau de points T en parcourant la liste L */
    int k = 0;                         /* indice de l'�l�ment dans T.tab */
    Cellule_Liste_Point *el = L.first; /* pointeur sur l'�l�ment dans L */
    while (el)
    {
        T.tab[k] = el->data;
        k++;           /* incr�menter k */
        el = el->suiv; /* passer � l'�lement suivant dans la liste chainee */
    }

    return T;
}

/* �crire le contour L � l'�cran
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acc�der aux �l�ments d'une
   s�quence de points par indice */
void ecrire_contour(Liste_Point L)
{
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;

    printf("%d points : [", nP);
    for (k = 0; k < nP; k++)
    {
        Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
        printf(" (%5.1f,%5.1f)", P.x, P.y);
    }
    printf("]\n");

    free(TP.tab); /* supprimer le tableau de point TP */
}

void ecrire_contour_fichier(Liste_Point L, char* nom_fichier)
{
    Tableau_Point TP = sequence_points_liste_vers_tableau(L);
    int k;
    int nP = TP.taille;

    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "1\n\n%d\n", nP-1);
        for (k = 0; k < nP; k++)
        {
            Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
            fprintf(fichier, " %5.1f %5.1f \n", P.x, P.y);
        }
        fprintf(fichier, "\n");
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier %s", nom_fichier);
    }

    free(TP.tab); /* supprimer le tableau de point TP */
}

// réecri les fonctions précédentes avec le type liste_contour

/* cr�er un �l�ment de liste de contour */
Cellule_Liste_Contour *creer_element_liste_Contour(Liste_Point v)
{
    Cellule_Liste_Contour *el;

    el = malloc(sizeof(Cellule_Liste_Contour));
    if (el == NULL)
    {
        fprintf(stderr, "creer_element_liste_Contour : ");
        fprintf(stderr, " allocation impossible\n");
        exit(-1);
    }
    el->data = v;
    el->suiv = NULL;
    return el;
}

/* cr�er une liste de contour vide */
Liste_Contour creer_liste_Contour(void)
{
    Liste_Contour L;

    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

/* ajouter un contour v � la fin de la liste L, renvoie la liste L modifi�e */
Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Liste_Point c)
{
    Cellule_Liste_Contour *el = creer_element_liste_Contour(c);

    if (L.taille == 0)
    {
        L.first = L.last = el;
    }
    else
    {
        L.last->suiv = el;
        L.last = el;
    }
    L.taille++;
    return L;
}

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */
Liste_Contour concatener_liste_Contour(Liste_Contour L1, Liste_Contour L2)
{
    /* cas o� l'une des deux listes est vide */
    if (L1.taille == 0)
        return L2;
    if (L2.taille == 0)
        return L1;

    /* les deux listes sont non vides */
    L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
    L1.last = L2.last;        /* le dernier �l�ment de L1 est celui de L2 */
    L1.taille += L2.taille;   /* nouvelle taille pour L1 */
    return L1;
}

/* cr�er une s�quence de contours sous forme d'un tableau de contours
   � partir de la liste de contours L */
Tableau_Contour sequence_contours_liste_vers_tableau(Liste_Contour L)
{
    Tableau_Contour T;

    /* taille de T = taille de L */
    T.taille = L.taille;

    /* allocation dynamique du tableau de Point */
    T.tab = malloc(sizeof(Liste_Point) * T.taille);
    if (T.tab == NULL)
    {
        /* allocation impossible : arret du programme avec un message */
        fprintf(stderr, "sequence_contours_liste_vers_tableau : ");
        fprintf(stderr, " allocation impossible\n");
        exit(-1);
    }

    /* remplir le tableau de contours T en parcourant la liste L */
    int k = 0;                         /* indice de l'�l�ment dans T.tab */
    Cellule_Liste_Contour *el = L.first; /* pointeur sur l'�l�ment dans L */
    while (el)
    {
        T.tab[k] = el->data;
        k++;           /* incr�menter k */
        el = el->suiv; /* passer � l'�lement suivant dans la liste chainee */
    }

    return T;
}

void ecrire_contours_fichier(Liste_Contour L, char *nom_fichier)
{
    int k;
    int nC = L.taille;
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur: ouverture du fichier %s impossible", nom_fichier);
    }
    Cellule_Liste_Contour *el = L.first;
    fprintf(fichier, "%d\n\n", nC);
    for (int i = 0; i < nC; i++)
    {
        Tableau_Point TP = sequence_points_liste_vers_tableau(el->data);
        int nP = TP.taille;

        if (fichier != NULL)
        {
            fprintf(fichier, "%d\n", nP - 1);
            for (k = 0; k < nP; k++)
            {
                Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
                fprintf(fichier, " %5.1f %5.1f \n", P.x, P.y);
            }
            fprintf(fichier, "\n");
            
        }
        else
        {
            printf("Impossible d'ouvrir le fichier %s", nom_fichier);
        }

        //free(TP.tab); /* supprimer le tableau de point TP */
        el = el->suiv;
    }
    fclose(fichier);
}