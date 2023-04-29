#include "liste_point.h"
#include "geom2d.h"
#include "simplifications.h"
#include <stdlib.h>
#include <math.h>

void decouper_liste_point(Liste_Point L, int i, Liste_Point *L1, Liste_Point *L2)
{
    Cellule_Liste_Point *C = L.first;
    int j = 0;
    while (C != NULL)
    {
        if (j < i)
        {
            *L1 = ajouter_element_liste_Point(*L1, C->data);
        }
        else
        {
            *L2 = ajouter_element_liste_Point(*L2, C->data);
        }
        C = C->suiv;
        j++;
    }
}

Contour simplification_douglas_peucker_segments(Contour Cont, double d)
{
    Tableau_Point C = sequence_points_liste_vers_tableau(Cont);
    int n = C.taille-1;
    double dmax = 0;
    int k = 0;
    for (int j =  1; j <= n; j++)
    {
        double dj = distance_point_segment(C.tab[j], C.tab[0], C.tab[n]);
        if (dj > dmax)
        {
            dmax = dj;
            k = j;
        }
    }
    Contour L = creer_liste_Point_vide();
    if (dmax <= d)
    {
        L = ajouter_element_liste_Point(L, C.tab[0]);
        L = ajouter_element_liste_Point(L, C.tab[n]);
    }
    else
    {
        Contour L1 = creer_liste_Point_vide();
        Contour L2 = creer_liste_Point_vide();
        decouper_liste_point(Cont, k, &L1, &L2);
        L1 = simplification_douglas_peucker_segments(L1, d);
        L2 = simplification_douglas_peucker_segments(L2, d);
        L = concatener_liste_Point(L1, L2);
    }
    return L;
}

double alpha_2(double n)
{
    return (3. * n) / (n * n - 1.);
}

double beta_2(double n)
{
    return (1. - 2. * n) / (2. * (n + 1.));
}

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

double alpha_3(int n)
{
    double N = (double)(n);
    return (-15. * pow(N, 3.) + 5. * pow(N, 2.) + 2. * N + 4.) / (3. * (N + 2.) * (3. * pow(N, 2.) + 1.));
}

double beta_3(int n)
{
    double N = (double)(n);
    return (10. * pow(N, 3.) - 15. * pow(N, 2.) + N + 2.) / (3. * (N + 2.) * (3. * pow(N, 2.) + 1.));
}

double lambda_3(int n)
{
    double N = (double)(n);
    return (70. * N) / (3. * (pow(N, 2.) - 1.) * (pow(N, 2.) - 4.) * (3. * pow(N, 2.) + 1.));
}

double gamma_3(int k, int n)
{
    double K = (double)(k);
    double N = (double)(n);
    return 6. * pow(K, 4.) - 8. * N * pow(K, 3.) + 6. * pow(K, 2.) - 4. * N * K + pow(N, 4.) + pow(N, 2.);
}

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