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
    Liste_Contour LC = calcul_contour(I);
    // On enlève l'extension .pgm de argv[1] pour ajouter .
    // contour à la fin

    char chemin_complet[256];
    creer_chemin_fichier_de_sortie(argv[1], "contours", "", chemin_complet);
    ecrire_contours_fichier(LC, chemin_complet);

    // Affichage nombre de contours et nombre total de segments
    printf("Nombre de contours : %d\n", LC.taille);
    int nb_segments = 0;
    Cellule_Liste_Contour *Cell = LC.first;
    while (Cell != NULL)
    {
        Contour C = Cell->data;
        nb_segments += ((C.taille - 1) / 2) + 1;
        Cell = Cell->suiv;
    }
    printf("Nombre de segments : %d\n", nb_segments);

    return 0;
}
