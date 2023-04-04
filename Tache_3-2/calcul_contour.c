#include "image.h"
#include "geom2d.h"
#include "liste_point.h"
#include "calcul_contour.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Point avancer(Point p, Orientation o)
{
    Point p_suiv = {p.x, p.y};
    switch (o)
    {
    case Nord:
        p_suiv.y = p.y - 1;
        break;
    case Est:
        p_suiv.x = p.x + 1;
        break;
    case Sud:
        p_suiv.y = p.y + 1;
        break;
    case Ouest:
        p_suiv.x = p.x - 1;
        break;
    }
    return p_suiv;
}

Orientation tourner(Orientation o, bool vers_la_droite)
{
    switch (o)
    {
    case Nord:
        if (vers_la_droite)
            return Est;
        else
            return Ouest;
    case Est:
        if (vers_la_droite)
            return Sud;
        else
            return Nord;
    case Sud:
        if (vers_la_droite)
            return Ouest;
        else
            return Est;
    case Ouest:
        if (vers_la_droite)
            return Nord;
        else
            return Sud;
    }
}

Point trouver_pixel_depart(Image I)
{
    Point P = {0, 0};
    for (int j = 0; j < hauteur_image(I); j++)
    {
        for (int i = 0; i < largeur_image(I); i++)
        {
            if (get_pixel_image(I,i,j) == 1 & get_pixel_image(I,i,j-1)==0)
            {
                P.x = i;
                P.y = j;
                return P;
            }
        }
    }
    return P;
}

Pixel get_pixel_relatif(Image I ,Point p, Orientation o, Direction d)
{
    switch (d)
    {
        case Avant_gauche:
            switch (o)
            {
                case Nord:
                    return get_pixel_image(I, p.x, p.y);
                case Est:
                    return get_pixel_image(I, p.x+1, p.y);
                case Sud:
                    return get_pixel_image(I, p.x+1, p.y+1);
                case Ouest:
                    return get_pixel_image(I, p.x, p.y+1);
            }
        case Avant_droit:
            switch (o)
            {
                case Nord:
                    return get_pixel_image(I, p.x+1, p.y);
                case Est:
                    return get_pixel_image(I, p.x+1, p.y+1);
                case Sud:
                    return get_pixel_image(I, p.x, p.y+1);
                case Ouest:
                    return get_pixel_image(I, p.x, p.y);
            }
        case Arriere_gauche:
            switch (o)
            {
                case Nord:
                    return get_pixel_image(I, p.x, p.y+1);
                case Est:
                    return get_pixel_image(I, p.x, p.y);
                case Sud:
                    return get_pixel_image(I, p.x+1, p.y);
                case Ouest:
                    return get_pixel_image(I, p.x+1, p.y+1);
            }
        case Arriere_droit:
            switch (o)
            {
                case Nord:
                    return get_pixel_image(I, p.x+1, p.y+1);
                case Est:
                    return get_pixel_image(I, p.x, p.y+1);
                case Sud:
                    return get_pixel_image(I, p.x, p.y);
                case Ouest:
                    return get_pixel_image(I, p.x+1, p.y);
            }
    }
}

Orientation nouvelle_orientation(Image I, Point pos, Orientation o)
{
    Pixel p_avant_gauche = get_pixel_relatif(I, pos, o, Avant_gauche);
    Pixel p_avant_droit = get_pixel_relatif(I, pos, o, Avant_droit);

    if (p_avant_gauche == 1)
    {
        return tourner(o, false);
    }
    else if (p_avant_droit == 1)
    {
        return o;
    }
    else
    {
        return tourner(o, true);
    }
}

Liste_Point calcul_contour(Image I, Point p_depart)
{
    Liste_Point L = creer_liste_Point_vide();
    Point p_robot = {p_depart.x - 1, p_depart.y - 1};
    Orientation o = Est;
    bool revenu_au_depart = false;
    while (!revenu_au_depart)
    {
        L = ajouter_element_liste_Point(L,p_robot);
        p_robot = avancer(p_robot, o);
        o = nouvelle_orientation(I, p_robot, o);
        if (p_robot.x == p_depart.x-1 && p_robot.y == p_depart.y-1 && o==Est)
        {
            revenu_au_depart = true;
        }
    }
    L = ajouter_element_liste_Point(L,p_robot);
    return L;
}