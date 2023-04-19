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

void ecrire_fichier_eps_bezier2(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin)
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
        Cellule_Liste_Point *cellule_C0 = C.first;
        Cellule_Liste_Point *cellule_C1;
        Cellule_Liste_Point *cellule_C2;
        fprintf(f, "%f %f moveto\n", C.first->data.x, hauteur - C.first->data.y);

        while (cellule_C0 != NULL)
        {
            cellule_C1 = cellule_C0->suiv;
            cellule_C2 = cellule_C1->suiv;
            Bezier2 B2;
            B2.C0 = cellule_C0->data;
            B2.C1 = cellule_C1->data;
            B2.C2 = cellule_C2->data;
            Bezier3 B3 = conversion_Bezier2_vers_Bezier3(B2);
            fprintf(f, "%f %f %f %f %f %f curveto\n", B3.C1.x, hauteur - B3.C1.y, B3.C2.x, hauteur - B3.C2.y, B3.C3.x, hauteur - B3.C3.y);
            cellule_C0 = cellule_C2->suiv;
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

void ecrire_fichier_eps_bezier3(Liste_Contour LC, unsigned int largeur, unsigned int hauteur, char *nom_fichier, Type_dessin type_dessin)
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
        Cellule_Liste_Point *cellule_C0 = C.first;
        Cellule_Liste_Point *cellule_C1;
        Cellule_Liste_Point *cellule_C2;
        Cellule_Liste_Point *cellule_C3;
        fprintf(f, "%f %f moveto\n", C.first->data.x, hauteur - C.first->data.y);

        while (cellule_C0 != NULL)
        {
            cellule_C1 = cellule_C0->suiv;
            cellule_C2 = cellule_C1->suiv;
            cellule_C3 = cellule_C2->suiv;
            Bezier3 B3;
            B3.C0 = cellule_C0->data;
            B3.C1 = cellule_C1->data;
            B3.C2 = cellule_C2->data;
            B3.C3 = cellule_C3->data;
            fprintf(f, "%f %f %f %f %f %f curveto\n", B3.C1.x, hauteur - B3.C1.y, B3.C2.x, hauteur - B3.C2.y, B3.C3.x, hauteur - B3.C3.y);
            cellule_C0 = cellule_C3->suiv;
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