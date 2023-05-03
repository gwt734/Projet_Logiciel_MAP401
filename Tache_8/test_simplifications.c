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
