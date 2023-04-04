#include <string.h>
#include "calcul_contour.h"
#include "liste_point.h"
#include "image.h"

int main(int argc, char **argv)
{
    Image I = lire_fichier_image(argv[1]);
    Point P = trouver_pixel_depart(I);
    Contour C = calcul_contour(I, P);
    // On enlève l'extension .pgm de argv[1] pour ajouter .
    // contour à la fin
    char nom_fichier_contour[strlen(argv[1]) - 4 + 8];
    strcpy(nom_fichier_contour, argv[1]);
    nom_fichier_contour[strlen(argv[1]) - 4] = '\0';
    ecrire_contour_fichier(C, strcat(nom_fichier_contour, ".contour"));
    return 0;
}
