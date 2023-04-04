#include "calcul_contour.h"
#include "image.h"

int main(int argc, char **argv)
{
    Image I = lire_fichier_image(argv[1]);
    Point P = trouver_pixel_depart(I);
    /*Contour C = */calcul_contour(I, P);
    /*ecrire_contour(C);*/
    return 0;
}
