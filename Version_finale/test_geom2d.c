#include <stdio.h>
#include "geom2d.h"

int main(int argc, char **argv)
{
    // Test unitaires des fonctions du module geom2d

    //      Test add_point
    Point P1 = set_point(1, 2);
    Point P2 = set_point(3, 4);
    Point P_resultat = add_point(P1, P2);
    Point P_attendu = set_point(4, 6);
    if (P_resultat.x != P_attendu.x || P_resultat.y != P_attendu.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur add_point\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest add_point : OK\033[0m\n");

    //      Test add_vect
    Vecteur V1 = set_vect(1, 2);
    Vecteur V2 = set_vect(3, 4);
    Vecteur V_resultat = add_vect(V1, V2);
    Vecteur V_attendu = set_vect(4, 6);
    if (V_resultat.x != V_attendu.x || V_resultat.y != V_attendu.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur add_vect\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest add_vect : OK\033[0m\n");

    //      Test vect_bipoint
    Point A = set_point(1, 2);
    Point B = set_point(3, 4);
    Vecteur V_resultat2 = vect_bipoint(A, B);
    Vecteur V_attendu2 = set_vect(2, 2);
    if (V_resultat2.x != V_attendu2.x || V_resultat2.y != V_attendu2.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur vect_bipoint\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest vect_bipoint : OK\033[0m\n");

    //      Test norme_vect
    Vecteur V = set_vect(3, 4);
    double norme_resultat = norme_vect(V);
    double norme_attendu = 5;
    if (norme_resultat != norme_attendu)
    {
        fprintf(stderr, "\t\033[0;31mErreur norme_vect\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest norme_vect : OK\033[0m\n");

    //      Test mult_scalaire
    Vecteur V3 = set_vect(1, 2);
    double k = 2;
    Vecteur V_resultat3 = mult_scalaire(V3, k);
    Vecteur V_attendu3 = set_vect(2, 4);
    if (V_resultat3.x != V_attendu3.x || V_resultat3.y != V_attendu3.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur mult_scalaire\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest mult_scalaire : OK\033[0m\n");
    
    //      Test mult_scalaire_point
    Point A2 = set_point(1, 2);
    double k2 = 2;
    Point P_resultat2 = mult_scalaire_point(A2, k2);
    Point P_attendu2 = set_point(2, 4);
    if (P_resultat2.x != P_attendu2.x || P_resultat2.y != P_attendu2.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur mult_scalaire_point\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest mult_scalaire_point : OK\033[0m\n");

    //      Test distance_points
    Point A3 = set_point(1, 2);
    Point B3 = set_point(1, 4);
    double distance_resultat = distance_points(A3, B3);
    double distance_attendu = 2;
    if (distance_resultat != distance_attendu)
    {
        fprintf(stderr, "\t\033[0;31mErreur distance_points\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest distance_points : OK\033[0m\n");

    //      Test produit scalaire
    Vecteur V4 = set_vect(1, 2);
    Vecteur V5 = set_vect(3, 4);
    double produit_resultat = produit_scalaire(V4, V5);
    double produit_attendu = 11;
    if (produit_resultat != produit_attendu)
    {
        fprintf(stderr, "\t\033[0;31mErreur produit_scalaire\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest produit_scalaire : OK\033[0m\n");

    //      Test angle_vect
    Vecteur V6 = set_vect(1, 2);
    Vecteur V7 = set_vect(4, 8);
    double angle_resultat = angle_vect(V6, V7);
    double angle_attendu = 0.0;
    if (angle_resultat < angle_attendu + PRECISION_EGALITE  && angle_resultat > angle_attendu + PRECISION_EGALITE)
    {
        fprintf(stderr, "\t\033[0;31mErreur angle_vect\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest angle_vect : OK\033[0m\n");

    //      Test vect_unitaire
    Vecteur V8 = set_vect(0, 3);
    Vecteur V_resultat4 = vect_unitaire(V8);
    Vecteur V_attendu4 = set_vect(0, 1);
    if (V_resultat4.x != V_attendu4.x || V_resultat4.y != V_attendu4.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur vect_unitaire\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest vect_unitaire : OK\033[0m\n");

    //      Test vect_normal
    Vecteur V9 = set_vect(1, 2);
    Vecteur V_resultat5 = vect_normal(V9);
    Vecteur V_attendu5 = set_vect(-2, 1);
    if (V_resultat5.x != V_attendu5.x || V_resultat5.y != V_attendu5.y)
    {
        fprintf(stderr, "\t\033[0;31mErreur vect_normal\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest vect_normal : OK\033[0m\n");

    //      Test distance_point_segment
    Point A4 = set_point(1, 0);
    Point B4 = set_point(3, 0);
    Point C4 = set_point(3, 2);
    double distance_resultat2 = distance_point_segment(A4, B4, C4);
    double distance_attendu2 = 2.0;
    if (distance_resultat2 != distance_attendu2)
    {
        fprintf(stderr, "\t\033[0;31mErreur distance_point_segment\033[0m\n");
        return 1;
    }
    printf("\033[0;32mTest distance_point_segment : OK\033[0m\n");

    printf("\n\033[0;32m => Tout les tests sont passés\033[0m\n");
    return 0;
}
