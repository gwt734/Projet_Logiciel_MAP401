#include "eps.h"
#include "liste_point.h"
#include <stdio.h>

void ecrire_fichier_eps(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin)
{
    FILE *f = fopen(nom_fichier, "w");
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %d %d\n", largeur, hauteur);
    fprintf(f, "0 setlinewidth\n");
    fprintf(f, "0 0 0 setrgbcolor\n");
    fprintf(f, "newpath\n");
    Cellule_Liste_Contour *cellule_contour = LC.first;
    while (cellule_contour != NULL)
    {
        Liste_Point C = cellule_contour->data;
        Cellule_Liste_Point *cellule_actuelle = C.first;
        fprintf(f, "%f %f moveto\n", C.first->data.x, hauteur - C.first->data.y);

        for (int i = 0; i < C.taille; i++)
        {
            fprintf(f, "%f %f lineto\n", cellule_actuelle->data.x, hauteur - cellule_actuelle->data.y);
            cellule_actuelle = cellule_actuelle->suiv;
        }

        cellule_contour = cellule_contour->suiv;
    }
    if (type_dessin == STROKE)
    {
        fprintf(f, "stroke\n");
    }
    else
    {
        fprintf(f, "fill\n");
    }
    fprintf(f, "showpage\n");
    fclose(f);
}
