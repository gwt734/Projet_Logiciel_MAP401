#include <string.h>
#include "calcul_contour.h"
#include "liste_point.h"
#include "image.h"
#include "nom_fichiers.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <image.pbm>\n", argv[0]);
        return 1;
    }
    Image I = lire_fichier_image(argv[1]);
    Liste_Contour C = calcul_contour(I);
    // On enlève l'extension .pgm de argv[1] pour ajouter .
    // contour à la fin

    char chemin_complet[256];
    creer_chemin_fichier_de_sortie(argv[1], "contours", "", chemin_complet);
    ecrire_contours_fichier(C, chemin_complet);
    return 0;
}
