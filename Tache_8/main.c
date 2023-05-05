#include "simplifications.h"
#include "eps.h"
#include "calcul_contour.h"
#include "image.h"
#include "nom_fichiers.h"

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
            Tableau_Point TC = sequence_points_liste_vers_tableau(C);
            C_simplifie = simplification_douglas_peucker_segments(TC, d);
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
    char chemin_complet_contour[256];
    creer_chemin_fichier_de_sortie(argv[1], "contours", "", chemin_complet_contour);
    ecrire_contours_fichier(L_C_simplifie, chemin_complet_contour);

    // Création du fichier eps
    Type_dessin type_dessin = FILL;
    char chemin_complet_eps[256];
    char suffixe_a_ajouter[32];
    if (deg == 1)
    {
        strcpy(suffixe_a_ajouter, "_sdp_segments");
    }
    else if (deg == 2)
    {
        strcpy(suffixe_a_ajouter, "_sdp_beziers2");
    }
    else if (deg == 3)
    {
        strcpy(suffixe_a_ajouter, "_sdp_beziers3");
    }
    sprintf(suffixe_a_ajouter + strlen(suffixe_a_ajouter), "_d=%.0f", d);
    creer_chemin_fichier_de_sortie(argv[1], "eps", suffixe_a_ajouter, chemin_complet_eps);
    
    if (deg == 1)
    {
        ecrire_fichier_eps(L_C_simplifie, largeur_image(I), hauteur_image(I), chemin_complet_eps, type_dessin);
    }
    else if (deg == 2)
    {
        ecrire_fichier_eps_bezier2(L_C_simplifie, largeur_image(I), hauteur_image(I), chemin_complet_eps, type_dessin);
    }
    else if (deg == 3)
    {
        ecrire_fichier_eps_bezier3(L_C_simplifie, largeur_image(I), hauteur_image(I), chemin_complet_eps, type_dessin);
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