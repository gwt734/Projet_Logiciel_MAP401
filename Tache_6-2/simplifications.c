#include "liste_point.h"
#include "geom2d.h"

Contour simplification_douglas_peucker(Contour Cont, int j1, int j2, double d)
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
        Contour L1 = simplification_douglas_peucker(Cont, j1, k, d);
        Contour L2 = simplification_douglas_peucker(Cont, k, j2, d);
        L = concatener_liste_Point(L1, L2);
    }
    return L;
}