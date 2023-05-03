#include <stdlib.h>
#include <stdio.h>
#include "image.h"

// prend en argument le nom du fichier image a tester
int main (int argc, char ** argv)
{
    if (argc != 2)
    {
        printf("Usage : nom du fichier image a tester");
        return 1;
    }
    Image I = lire_fichier_image(argv[1]);
    ecrire_image(I);
    /*Image neg_I = negatif_image(I);
    ecrire_image(neg_I);
    ecrire_image(I);*/
    return 0;
}