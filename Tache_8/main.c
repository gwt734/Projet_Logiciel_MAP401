#include "simplifications.h"
#include "eps.h"
#include "calcul_contour.h"
#include "image.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <image.pbm> <distance d> <degre courbe de Bezier>\n", argv[0]);
        return 1;
    }
    Image I = lire_fichier_image(argv[1]);
    double d = atof(argv[2]);

    int deg = atoi(argv[3]);

    // Simplification des contours
    Liste_Contour L_C = calcul_contour(I);
    Liste_Contour L_C_simplifie = creer_liste_Contour();
    Cellule_Liste_Contour *Cell = L_C.first;
    while (Cell != NULL)
    {
        Contour C = Cell->data;
        Contour C_simplifie;
        if (deg == 1)
        {
            C_simplifie = simplification_douglas_peucker_segments(sous_sequence_points_liste(C, 0, C.taille - 1), d);
        }
        else if (deg == 2)
        {
            C_simplifie = simplification_douglas_peucker_bezier2(C, 0, C.taille - 1, d);
        }
        else if (deg == 3)
        {
            C_simplifie = simplification_douglas_peucker_bezier3(C, 0, C.taille - 1, d);
        }
        L_C_simplifie = ajouter_element_liste_Contour(L_C_simplifie, C_simplifie);
        Cell = Cell->suiv;
    }

    // Création du fichier contour
    char nom_fichier_contour[strlen(argv[1]) - 4 + 4 + strlen(argv[2]) + 8];
    strcpy(nom_fichier_contour, argv[1]);
    nom_fichier_contour[strlen(argv[1]) - 4] = '\0';
    strcat(nom_fichier_contour, "_sdp");
    strcat(nom_fichier_contour, argv[2]);
    ecrire_contours_fichier(L_C_simplifie, strcat(nom_fichier_contour, ".contour"));

    // Création du fichier eps
    char nom_fichier_eps[strlen(argv[1]) - 4 + 4 + strlen(argv[2]) + 8];
    strcpy(nom_fichier_eps, argv[1]);
    nom_fichier_eps[strlen(argv[1]) - 4] = '\0';
    Type_dessin type_dessin = FILL;
    strcat(nom_fichier_eps, "_sdp");
    strcat(nom_fichier_eps, argv[2]);

    if (deg == 1)
    {
        strcat(nom_fichier_eps, "_segment");
        ecrire_fichier_eps(L_C_simplifie, largeur_image(I), hauteur_image(I), strcat(nom_fichier_eps, ".eps"), type_dessin);
    }
    else if (deg == 2)
    {
        strcat(nom_fichier_eps, "_b2");
        ecrire_fichier_eps_bezier2(L_C_simplifie, largeur_image(I), hauteur_image(I), strcat(nom_fichier_eps, ".eps"), type_dessin);
    }
    else if (deg == 3)
    {
        strcat(nom_fichier_eps, "_b3");
        ecrire_fichier_eps_bezier3(L_C_simplifie, largeur_image(I), hauteur_image(I), strcat(nom_fichier_eps, ".eps"), type_dessin);
    }

    // Affichage nombre de contours et nombre total de segments
    printf("Nombre de contours : %d\n", L_C_simplifie.taille);

    if (deg == 1)
    {
        int nb_segments = 0;
        Cell = L_C_simplifie.first;
        while (Cell != NULL)
        {
            Contour C = Cell->data;
            nb_segments += ((C.taille - 1) / 2) + 1;
            Cell = Cell->suiv;
        }
        printf("Nombre de segments : %d\n", nb_segments);
    }
    else if (deg == 2)
    {
        int nb_courbes = 0;
        Cell = L_C_simplifie.first;
        while (Cell != NULL)
        {
            Contour C = Cell->data;
            nb_courbes += ((C.taille - 1) / 3) + 1;
            Cell = Cell->suiv;
        }
        printf("Nombre de courbes : %d\n", nb_courbes);
    }
    else if (deg == 3)
    {
        int nb_courbes = 0;
        Cell = L_C_simplifie.first;
        while (Cell != NULL)
        {
            Contour C = Cell->data;
            nb_courbes += ((C.taille - 1) / 4) + 1;
            Cell = Cell->suiv;
        }
        printf("Nombre de courbes : %d\n", nb_courbes);
    }
    return 0;
}