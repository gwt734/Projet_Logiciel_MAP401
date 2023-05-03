#ifndef NOM_FICHIERS_H
#define NOM_FICHIERS_H

/*
 * Module de manipulation de nom de fichier et de chemins
*/

/*
 * Fonction qui extrait le nom d'un fichier (avec extension si il y en a) a partir du chemin vers ce fichier
 * Entrées :
 *  - chemin_complet : le chemin du fichier
 *  - nom_fichier : la chaine de caractère qui recevra le nom du fichier extrait
*/
void extraction_nom_fichier(char *chemin_complet, char *nom_fichier);

/*
 * Fonction qui extrait le nom du répertoire d'un fichier a partir du chemin vers ce fichier
 * Entrées :
 *  - chemin_complet : le chemin du fichier
 *  - nom_repertoire : la chaine de caractère qui recevra le nom du repertoire extrait
*/
void extraction_nom_repertoire(char *chemin_complet, char *nom_repertoire);

/*
    * Fonction qui extrait l'extension d'un fichier a partir du nom du fichier
    * Entrées :
    *  - nom_fichier : le nom du fichier
    *  - extension : la chaine de caractère qui recevra l'extension extraite
*/
void extraction_extension(char *nom_fichier, char *extension);

/*
    * Fonction qui extrait le nom d'un fichier sans extension a partir du nom du fichier
    * Entrées :
    *  - nom_fichier : le nom du fichier
    *  - nom_fichier_sans_extension : la chaine de caractère qui recevra le nom du fichier sans extension extrait
*/
void extraction_nom_fichier_sans_extension(char *nom_fichier, char *extraction_nom_fichier_sans_extension);

/*
    * Fonction qui crée le nom d'un fichier de sortie a partir du chemin d'un fichier d'entrée, d'une extension et d'un suffixe a ajouter
    * Entrées :
    *  - chemin_fichier : le chemin du fichier d'entrée
    *  - extension : l'extension du fichier de sortie
    *  - suffixe_a_ajouter : le suffixe a ajouter au nom du fichier de sortie
    *  - chemin_fichier_de_sortie : la chaine de caractère qui recevra le chemin du fichier de sortie
*/
void creer_chemin_fichier_de_sortie(char *chemin_fichier, char *extension, char *suffixe_a_ajouter, char *chemin_fichier_de_sortie);

#endif