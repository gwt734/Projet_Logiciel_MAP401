#include "eps.h"
#include "calcul_contour.h"
#include "image.h"
#include "nom_fichiers.h"
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <image.pbm> <type de tracé>\n", argv[0]);
        return 1;
    }

    Image I = lire_fichier_image(argv[1]);
    Liste_Contour LC = calcul_contour(I);

    //Nomenclature de fichier
    char chemin_complet[256];
    char suffixe_a_ajouter[32];

    Type_dessin type_dessin;
    if (strcmp(argv[2], "fill") == 0)
    {
        type_dessin = FILL;
        strcpy(suffixe_a_ajouter, "_fill");
    }
    else if (strcmp(argv[2], "stroke") ==0 )
    {
        type_dessin = STROKE;
        strcpy(suffixe_a_ajouter, "_stroke");
    }
    
    creer_chemin_fichier_de_sortie(argv[1], "eps", suffixe_a_ajouter, chemin_complet);
    ecrire_fichier_eps(LC, largeur_image(I), hauteur_image(I), chemin_complet, type_dessin);
}