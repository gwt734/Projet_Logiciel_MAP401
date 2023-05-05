#include <string.h>
#include "calcul_contour.h"
#include "liste_point.h"
#include "image.h"

int main(int argc, char **argv)
{
    Image I = lire_fichier_image(argv[1]);
    Liste_Contour LC = calcul_contour(I);
    // On enlève l'extension .pgm de argv[1] pour ajouter .
    // contour à la fin
    char nom_fichier_contour[strlen(argv[1]) - 4 + 8];
    strcpy(nom_fichier_contour, argv[1]);
    nom_fichier_contour[strlen(argv[1]) - 4] = '\0';

    ecrire_contours_fichier(LC, strcat(nom_fichier_contour, ".contour"));
    return 0;
}
