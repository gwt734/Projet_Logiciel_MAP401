#include "nom_fichiers.h"

#include <string.h>

void extraction_nom_fichier(char *chemin_complet, char *nom_fichier)
{
    char *nom = strrchr(chemin_complet, '/');
    if (nom == NULL)
    {
        strcpy(nom_fichier, chemin_complet);
    }
    else
    {
        strcpy(nom_fichier, nom + 1);
    }
}

void extraction_nom_repertoire(char *chemin_complet, char *nom_repertoire)
{
    char *nom = strrchr(chemin_complet, '/');
    if (nom == NULL)
    {
        strcpy(nom_repertoire, "");
    }
    else
    {
        strncpy(nom_repertoire, chemin_complet, nom - chemin_complet);
        nom_repertoire[nom - chemin_complet] = '\0';
    }
}

void extraction_extension(char *nom_fichier, char *extension)
{
    char *ext = strrchr(nom_fichier, '.');
    if (ext == NULL)
    {
        strcpy(extension, "");
    }
    else
    {
        strcpy(extension, ext + 1);
    }
}

void extraction_nom_fichier_sans_extension(char *nom_fichier, char *nom_fichier_sans_extension)
{
    char *ext = strrchr(nom_fichier, '.');
    if (ext == NULL)
    {
        strcpy(nom_fichier_sans_extension, nom_fichier);
    }
    else
    {
        strncpy(nom_fichier_sans_extension, nom_fichier, ext - nom_fichier);
        nom_fichier_sans_extension[ext - nom_fichier] = '\0';
    }
}

void creer_chemin_fichier_de_sortie(char *chemin_fichier, char *extension, char *suffixe_a_ajouter, char *chemin_fichier_de_sortie)
{
    char nom_fichier_sans_extension[256];
    extraction_nom_fichier(chemin_fichier, nom_fichier_sans_extension);
    extraction_nom_fichier_sans_extension(nom_fichier_sans_extension, nom_fichier_sans_extension);
    strcpy(chemin_fichier_de_sortie, "../Sorties_");
    strcat(chemin_fichier_de_sortie, extension);
    strcat(chemin_fichier_de_sortie, "/");
    strcat(chemin_fichier_de_sortie, nom_fichier_sans_extension);
    strcat(chemin_fichier_de_sortie, suffixe_a_ajouter);
    strcat(chemin_fichier_de_sortie, ".");
    strcat(chemin_fichier_de_sortie, extension);
}
