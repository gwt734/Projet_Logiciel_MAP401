# Compte rendu Tache 7 partie 2

## Module `simplification`

```c
/*
 * Simplification de Douglas-Peucker

 * Cont: contour à simplifier
 * j1: indice du premier point du contour à simplifier
 * j2: indice du dernier point du contour à simplifier
 * d: distance maximale entre le point et la droite
 *
 * retourne: le contour simplifié
 */
Contour simplification_douglas_peucker_segments(Contour Cont, int j1, int j2, double d)
{
    Tableau_Point C = sequence_points_liste_vers_tableau(Cont);
    double dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j < j2; j++)
    {
        double dj = distance_point_segment(C.tab[j], C.tab[j1], C.tab[j2]);
        if (dj > dmax)
        {
            dmax = dj;
            k = j;
        }
    }
    Contour L = creer_liste_Point_vide();
    if (dmax <= d)
    {
        L = ajouter_element_liste_Point(L, C.tab[j1]);
        L = ajouter_element_liste_Point(L, C.tab[j2]);
    }
    else
    {
        Contour L1 = simplification_douglas_peucker_segments(Cont, j1, k, d);
        Contour L2 = simplification_douglas_peucker_segments(Cont, k, j2, d);
        L = concatener_liste_Point(L1, L2);
    }
    return L;
}

/*
 * Coefficient alpha de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 2

 * n: nombre de points du contour à simplifier

 * retourne: le coefficient alpha
 */
double alpha_2(double n)
{
    return (3. * n) / (n * n - 1.);
}

/*
 * Coefficient beta de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 2

 * n: nombre de points du contour à simplifier

 * retourne: le coefficient beta
 */
double beta_2(double n)
{
    return (1. - 2. * n) / (2. * (n + 1.));
}

/*
 * Approximation d'un contour par une courbe de Bézier de degré 2

 * C: contour à approximer

 * retourne: la courbe de Bézier approximée
 */
Bezier2 approx_bezier2(Contour C)
{
    Bezier2 B;
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    B.C0 = T.tab[0];
    B.C2 = T.tab[T.taille - 1];
    int n = T.taille - 1;
    if (n == 1)
    {
        B.C1 = mult_scalaire_point(add_point(B.C0, B.C2), 0.5);
    }
    else
    {
        double a = alpha_2((double)n);
        double b = beta_2((double)n);
        Point somme = {0, 0};

        for (int i = 1; i < n; i++)
        {
            somme = add_point(somme, T.tab[i]);
        }
        B.C1 = add_point(mult_scalaire_point(somme, a), mult_scalaire_point(add_point(B.C0, B.C2), b));
    }

    return B;
}

/*
 * Sous-séquence d'un contour

 * CONT: contour
 * j1: indice du premier point de la séquence à extraire
 * j2: indice du dernier point de la séquence à extraire
 *
 * retourne: la sous séquence
 */
Contour sous_sequence_points_liste(Contour CONT, int j1, int j2)
{
    Contour L = creer_liste_Point_vide();
    int i = 0;
    Cellule_Liste_Point *C = CONT.first;
    while (C != NULL && i <= j2)
    {
        if (i >= j1 && i <= j2)
        {
            L = ajouter_element_liste_Point(L, C->data);
        }
        C = C->suiv;
        i++;
    }
    return L;
}

/*
 * Simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 2

 * CONT: contour à simplifier
 * j1: indice du premier point du contour à simplifier
 * j2: indice du dernier point du contour à simplifier
 * d: distance maximale entre le point et la droite
 *
 * retourne: le contour simplifié
 */
Contour simplification_douglas_peucker_bezier2(Contour CONT, int j1, int j2, double d)
{
    int n = j2 - j1;
    Contour L = creer_liste_Point_vide();
    Tableau_Point T = sequence_points_liste_vers_tableau(CONT);
    Bezier2 B = approx_bezier2(sous_sequence_points_liste(CONT, j1, j2));
    double dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j < j2; j++)
    {
        double ti = (double)(j - j1) / (double)n;
        double dj = distance_point_bezier2(T.tab[j], B, ti);
        if (dj > dmax)
        {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d)
    {
        L = ajouter_element_liste_Point(L, B.C0);
        L = ajouter_element_liste_Point(L, B.C1);
        L = ajouter_element_liste_Point(L, B.C2);
    }
    else
    {
        Contour L1 = simplification_douglas_peucker_bezier2(CONT, j1, k, d);
        Contour L2 = simplification_douglas_peucker_bezier2(CONT, k, j2, d);
        L = concatener_liste_Point(L1, L2);
    }
    return L;
}
```

## Programme `test_simplifications`

```c
#include "simplifications.h"
#include "geom2d.h"
#include "liste_point.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    bool tests_reussis = true;

    // ********************   Bezier de degré 2   ******************** //
    printf("********************   Bezier de degré 2   ********************\n");

    // Test du cas 1 seul segment
    printf("Test du cas 1 seul segment\n");
    srand(time(NULL));
    Contour C = creer_liste_Point_vide();
    Point P0 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    Point P1 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    C = ajouter_element_liste_Point(C, P0);
    C = ajouter_element_liste_Point(C, P1);
    Bezier2 B = approx_bezier2(C);
    int nb_reussites = 3;
    if (!est_environ_egal_points(B.C0, P0))
    {
        printf("\t\033[0;31mFAIL: B.C0 != P0\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B.C1, mult_scalaire_point(add_point(P0, P1), 0.5)))
    {
        printf("\t\033[0;31mFAIL: B.C1 != (P0 + P1) / 2\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B.C2, P1))
    {
        printf("\t\033[0;31mFAIL: B.C2 != P1\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 3)
    {
        printf("\t\033[0;32mSUCCESS: Test pour 1 segment validé\033[0m\n");
    }

    // Test du cas au moins 2 segments
    printf("Test du cas au moins 2 segments\n");
    C = creer_liste_Point_vide();
    double n = (double)(rand() % 100);

    Point Q0 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    Point Q1 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    Point Q2 = set_point((double)(rand() % 1000), (double)(rand() % 1000));

    B.C0 = Q0;
    B.C1 = Q1;
    B.C2 = Q2;

    for (int i = 0; i <= (int)n; i++)
    {
        C = ajouter_element_liste_Point(C, calcul_point_bezier2(B, (double)i / n));
    }

    Bezier2 B2 = approx_bezier2(C);

    nb_reussites = 3;
    if (!est_environ_egal_points(B2.C0, Q0))
    {
        printf("\t\033[0;31mFAIL: B2.C0 != Q0\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B2.C1, Q1))
    {
        printf("\t\033[0;31mFAIL: B2.C1 != Q1\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B2.C2, Q2))
    {
        printf("\t\033[0;31mFAIL: B2.C2 != Q2\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 3)
    {
        printf("\t\033[0;32mSUCCESS: Test pour au moins 2 segments validé\033[0m\n");
    }

    // Test de l'exemple du cours
    printf("Test de l'exemple du cours\n");
    C = creer_liste_Point_vide();
    P0 = set_point(0, 0);
    Point P8 = set_point(5, 3);
    C = ajouter_element_liste_Point(C, P0);
    C = ajouter_element_liste_Point(C, set_point(1, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 1));
    C = ajouter_element_liste_Point(C, set_point(1, 2));
    C = ajouter_element_liste_Point(C, set_point(2, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 3));
    C = ajouter_element_liste_Point(C, set_point(4, 3));
    C = ajouter_element_liste_Point(C, P8);

    Bezier2 B3 = approx_bezier2(C);

    Point C1_attendu = set_point(2600. / 1680., 4120. / 1680.);

    nb_reussites = 3;
    if (!est_environ_egal_points(B3.C0, P0))
    {
        printf("\t\033[0;31mFAIL: B3.C0 != P0\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B3.C1, C1_attendu))
    {
        printf("\t\033[0;31mFAIL: B3.C1 != (1.547619, 2.452381)\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B3.C2, P8))
    {
        printf("\t\033[0;31mFAIL: B3.C2 != P8\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 3)
    {
        printf("\t\033[0;32mSUCCESS: Test pour l'exemple du cours validé\033[0m\n");
    }

    // ********************        Résultat       ******************** //
    printf("********************        Résultat       ********************\n");
    if (tests_reussis)
    {
        printf("\033[0;32mSUCCESS: Tous les tests ont été validés\033[0m\n");
        return 0;
    }
    else
    {
        printf("\033[0;31mFAIL: Au moins un test n'a pas été validé\033[0m\n");
        return 1;
    }
}
```

## Programme principal

```c
#include "simplifications.h"
#include "eps.h"
#include "calcul_contour.h"
#include "image.h"
#include "nom_fichiers.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Vérification du nombre d'arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <image.pbm> <distance d> <degre courbe de Bezier>\n", argv[0]);
        return 1;
    }

    // Récupération des arguments
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
            C_simplifie = simplification_douglas_peucker_segments(C, 0, C.taille - 1, d);
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

    //      Préparation du nom du fichier de sortie
    Type_dessin type_dessin = FILL;
    char chemin_complet_eps[256];
    char suffixe_a_ajouter[32];
    if (deg == 1)
    {
        strcpy(suffixe_a_ajouter, "_segments");
    }
    else if (deg == 2)
    {
        strcpy(suffixe_a_ajouter, "_beziers2");
    }
    else if (deg == 3)
    {
        strcpy(suffixe_a_ajouter, "_beziers3");
    }
    sprintf(suffixe_a_ajouter + strlen(suffixe_a_ajouter), "_d=%.0f", d);
    creer_chemin_fichier_de_sortie(argv[1], "eps", suffixe_a_ajouter, chemin_complet_eps);

    //      Création du fichier
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

    // Affichage nombre de contours et nombre total de segments/courbes
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
```

## Tableau récapitulatif

![Tableau bezier 2](Tableau_Bezier2.png)
