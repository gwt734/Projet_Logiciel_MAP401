# Compte rendu Tache 7

## Partie 1

### Module `simplification`

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

/*
 * Coefficient alpha de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 *
 * n: nombre de points du contour à simplifier
 *
 * retourne: le coefficient alpha
 */
double alpha_3(int n)
{
    double N = (double)(n);
    return (-15. * pow(N, 3.) + 5. * pow(N, 2.) + 2. * N + 4.) / (3. * (N + 2.) * (3. * pow(N, 2.) + 1.));
}

/*
 * Coefficient beta de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 *
 * n: nombre de points du contour à simplifier
 *
 * retourne: le coefficient beta
 */
double beta_3(int n)
{
    double N = (double)(n);
    return (10. * pow(N, 3.) - 15. * pow(N, 2.) + N + 2.) / (3. * (N + 2.) * (3. * pow(N, 2.) + 1.));
}

/*
 * Coefficient lambda de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 *
 * n: nombre de points du contour à simplifier
 *
 * retourne: le coefficient lambda
 */
double lambda_3(int n)
{
    double N = (double)(n);
    return (70. * N) / (3. * (pow(N, 2.) - 1.) * (pow(N, 2.) - 4.) * (3. * pow(N, 2.) + 1.));
}

/*
 * Coefficient gamma de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 *
 * k: indice du point du contour à simplifier
 * n: nombre de points du contour à simplifier
 *
 * retourne: le coefficient gamma
 */
double gamma_3(int k, int n)
{
    double K = (double)(k);
    double N = (double)(n);
    return 6. * pow(K, 4.) - 8. * N * pow(K, 3.) + 6. * pow(K, 2.) - 4. * N * K + pow(N, 4.) - pow(N, 2.);
}

/*
 * Approximation d'un contour par une courbe de Bézier de degré 3
 *
 * C: contour à approximer
 *
 * retourne: la courbe de Bézier approximée
 */
Bezier3 approx_bezier3(Contour C)
{
    Bezier3 B;
    Tableau_Point T = sequence_points_liste_vers_tableau(C);
    int n = T.taille - 1;
    if (n <= 2)
    {
        B = conversion_Bezier2_vers_Bezier3(approx_bezier2(C));
    }
    else
    {
        B.C0 = T.tab[0];
        B.C3 = T.tab[n];
        double a = alpha_3(n);
        double b = beta_3(n);
        double l = lambda_3(n);
        Point somme;

        // Calcul de C1
        somme = set_point(0, 0);
        for (int i = 1; i <= n - 1; i++)
        {
            somme = add_point(somme, mult_scalaire_point(T.tab[i], gamma_3(i, n)));
        }
        B.C1 = add_point(mult_scalaire_point(B.C0, a), add_point(mult_scalaire_point(somme, l), mult_scalaire_point(B.C3, b)));
        
        // Calcul de C2
        somme = set_point(0, 0);
        for (int i = 1; i <= n - 1; i++)
        {
            somme = add_point(somme, mult_scalaire_point(T.tab[i], gamma_3(n - i, n)));
        }
        B.C2 = add_point(mult_scalaire_point(B.C0, b), add_point(mult_scalaire_point(somme, l), mult_scalaire_point(B.C3, a)));
    }
    return B;
}

/*
 * Simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 *
 * CONT: contour à simplifier
 * j1: indice du premier point du contour à simplifier
 * j2: indice du dernier point du contour à simplifier
 * d: distance maximale entre le point et la droite
 *
 * retourne: le contour simplifié
 */
Contour simplification_douglas_peucker_bezier3(Contour CONT, int j1, int j2, double d)
{
    int n = j2 - j1;
    Contour L = creer_liste_Point_vide();
    Tableau_Point T = sequence_points_liste_vers_tableau(CONT);
    Bezier3 B = approx_bezier3(sous_sequence_points_liste(CONT, j1, j2));
    double dmax = 0;
    int k = j1;
    for (int j = j1 + 1; j < j2; j++)
    {
        double ti = (double)(j - j1) / (double)n;
        double dj = distance_point_bezier3(T.tab[j], B, ti);
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
        L = ajouter_element_liste_Point(L, B.C3);
    }
    else
    {
        Contour L1 = simplification_douglas_peucker_bezier3(CONT, j1, k, d);
        Contour L2 = simplification_douglas_peucker_bezier3(CONT, k, j2, d);
        L = concatener_liste_Point(L1, L2);
    }
    return L;
}
```

### Programme `test_simplifications`

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

    // ********************   Bezier de degré 3   ******************** //
    printf("********************   Bezier de degré 3   ********************\n");

    // Test du cas 1 seul segment
    printf("Test du cas 1 seul segment\n");
    C = creer_liste_Point_vide();
    P0 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    P1 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    C = ajouter_element_liste_Point(C, P0);
    C = ajouter_element_liste_Point(C, P1);

    Bezier3 B4 = approx_bezier3(C);

    nb_reussites = 4;

    if (!est_environ_egal_points(B4.C0, P0))
    {
        printf("\t\033[0;31mFAIL: B4.C0 != P0\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B4.C1, mult_scalaire_point(add_point(mult_scalaire_point(P0, 2), P1), 1. / 3.)))
    {
        printf("\t\033[0;31mFAIL: B4.C1 != (P0 + P1) / 2\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B4.C2, mult_scalaire_point(add_point(mult_scalaire_point(P1, 2), P0), 1. / 3.)))
    {
        printf("\t\033[0;31mFAIL: B4.C2 != (P0 + P1) / 2\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B4.C3, P1))
    {
        printf("\t\033[0;31mFAIL: B4.C3 != P1\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 4)
    {
        printf("\t\033[0;32mSUCCESS: Test pour 1 seul segment validé\033[0m\n");
    }

    // Test du cas 2 segments
    printf("Test du cas 2 segments\n");
    Point P2;

    C = creer_liste_Point_vide();
    P0 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    P1 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    P2 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    C = ajouter_element_liste_Point(C, P0);
    C = ajouter_element_liste_Point(C, P1);
    C = ajouter_element_liste_Point(C, P2);

    Bezier3 B5 = approx_bezier3(C);

    nb_reussites = 4;

    if (!est_environ_egal_points(B5.C0, P0))
    {
        printf("\t\033[0;31mFAIL: B5.C0 != P0\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B5.C1, mult_scalaire_point(add_point(mult_scalaire_point(P1, 4), mult_scalaire_point(P2, -1)), 1. / 3.)))
    {
        printf("\t\033[0;31mFAIL: B5.C1 != (P0 + P1) / 2\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B5.C2, mult_scalaire_point(add_point(mult_scalaire_point(P1, 4), mult_scalaire_point(P0, -1)), 1. / 3.)))
    {
        printf("\t\033[0;31mFAIL: B5.C2 != (P0 + P1) / 2\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B5.C3, P2))
    {
        printf("\t\033[0;31mFAIL: B5.C3 != P1\033[0m\n");
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 4)
    {
        printf("\t\033[0;32mSUCCESS: Test pour 2 segments validé\033[0m\n");
    }

    // Test du cas au moins 3 segments
    printf("Test du cas au moins 3 segments\n");

    Point Q3;
    Q0 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    Q1 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    Q2 = set_point((double)(rand() % 1000), (double)(rand() % 1000));
    Q3 = set_point((double)(rand() % 1000), (double)(rand() % 1000));

    Bezier3 B6;
    B6.C0 = Q0;
    B6.C1 = Q1;
    B6.C2 = Q2;
    B6.C3 = Q3;

    C = creer_liste_Point_vide();

    n = (double)(rand() % 100);

    for (int i = 0; i <= (int)n; i++)
    {
        C = ajouter_element_liste_Point(C, calcul_point_bezier3(B6, (double)i / n));
    }

    Bezier3 B7 = approx_bezier3(C);

    nb_reussites = 4;

    if (!est_environ_egal_points(B7.C0, Q0))
    {
        printf("\t\033[0;31mFAIL: B7.C0 != Q0\033[0m\n");

        printf("\t %f, %f = %f, %f\n", B7.C0.x, B7.C0.y, Q0.x, Q0.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B7.C1, Q1))
    {
        printf("\t\033[0;31mFAIL: B7.C1 != Q1\033[0m\n");
        printf("\t %f, %f = %f, %f\n", B7.C1.x, B7.C1.y, Q1.x, Q1.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B7.C2, Q2))
    {
        printf("\t\033[0;31mFAIL: B7.C2 != Q2\033[0m\n");
        printf("\t %f, %f = %f, %f\n", B7.C2.x, B7.C2.y, Q2.x, Q2.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B7.C3, Q3))
    {
        printf("\t\033[0;31mFAIL: B7.C3 != Q3\033[0m\n");

        printf("\t %f, %f = %f, %f\n", B7.C3.x, B7.C3.y, Q3.x, Q3.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 4)
    {
        printf("\t\033[0;32mSUCCESS: Test pour au moins 3 segments validé\033[0m\n");
    }

    // Test exemple du cours
    printf("Test exemple du cours\n");

    C = creer_liste_Point_vide();
    P0 = set_point(0, 0);
    P8 = set_point(5, 3);
    C = ajouter_element_liste_Point(C, P0);
    C = ajouter_element_liste_Point(C, set_point(1, 0));
    C = ajouter_element_liste_Point(C, set_point(1, 1));
    C = ajouter_element_liste_Point(C, set_point(1, 2));
    C = ajouter_element_liste_Point(C, set_point(2, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 2));
    C = ajouter_element_liste_Point(C, set_point(3, 3));
    C = ajouter_element_liste_Point(C, set_point(4, 3));
    C = ajouter_element_liste_Point(C, P8);

    Bezier3 B8 = approx_bezier3(C);

    Point C2_attendu;
    C1_attendu = set_point(9053. / 5211., 4843. / 5211.);
    C2_attendu = set_point(9610. / 5211., 18182. / 5211.);

    nb_reussites = 4;

    if (!est_environ_egal_points(B8.C0, P0))
    {
        printf("\t\033[0;31mFAIL: B8.C0 != P0\033[0m\n");
        printf("\t %f, %f = %f, %f\n", B8.C0.x, B8.C0.y, P0.x, P0.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B8.C1, C1_attendu))
    {
        printf("\t\033[0;31mFAIL: B8.C1 != C1_attendu\033[0m\n");
        printf("\t %f, %f = %f, %f\n", B8.C1.x, B8.C1.y, C1_attendu.x, C1_attendu.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B8.C2, C2_attendu))
    {
        printf("\t\033[0;31mFAIL: B8.C2 != C2_attendu\033[0m\n");
        printf("\t %f, %f = %f, %f\n", B8.C2.x, B8.C2.y, C2_attendu.x, C2_attendu.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (!est_environ_egal_points(B8.C3, P8))
    {
        printf("\t\033[0;31mFAIL: B8.C3 != P8\033[0m\n");
        printf("\t %f, %f = %f, %f\n", B8.C3.x, B8.C3.y, P8.x, P8.y);
        tests_reussis = false;
        nb_reussites--;
    }
    if (nb_reussites == 4)
    {
        printf("\t\033[0;32mSUCCESS: Test exemple du cours validé\033[0m\n");
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

### Tableau récapitulatifs

### Image `Asterix3`

| ![Asterix3](/home/gwendal/Downloads/Asterix3.svg) | ![Asterix3](/home/gwendal/Downloads/Asterix3_sdp1_b2.svg) | ![Asterix3](/home/gwendal/Downloads/Asterix3_sdp3_b2.svg) | ![Asterix3](/home/gwendal/Downloads/Asterix3_sdp10_b2.svg) | ![Asterix3](/home/gwendal/Downloads/Asterix3_sdp30_b2.svg) |
| ------------------------------------------------- | ------------------------------------------------- | ------------------------------------------------- | -------------------------------------------------- | -------------------------------------------------- |
|                                                   |                                                   |                                                   |                                                    |                                                    |
