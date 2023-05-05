# Projet logiciel : Vectorisation et simplification d'images bitmap

## Structure du projet

### Répertoires

- `Tache_<n>` : les fichiers sauvegardés à la fin de chaque tache
- `Version_finale` : la version finale de ce projet
- `Readme_files` : les fichiers utilisés pour la création du Readme
- `Images_Test` : Les images créés durant le projet pour les tests
- `IMAGES` : Les images fournies
- `Sorties_EPS` : Les fichiers EPS générés par les programmes
- `Sorties_contours` : Les fichiers contours générés par les programmes

### Fichiers

- `main` : programme principal qui extrait le contour d'une image donnée puis le simplifie et produit une sortie au format eps
- `image` : module de manipulation d'images bitmap
- `geom2D` : module de manipulation de vecteurs et de points
- `calcul_contour` : module de calculs de contour
- `nom_fichier` : module de manipulation de nom et de chemins de fichier
- `simplification` : module de simplification de contours qui contient les trois méthodes : par segments, courbes de bézier de degré 2 et 3
- `test_X` : programme de test associé au module ou à la fonction X
- `Makefile` : fichier de compilation
- `<scripts_bash>` : scripts utilisés pour faciliter la soutenance et l'écrtiture des rapports.

## Processus de construction du projet

### Tâche 1

#### Paquetage Image

- **Écriture de la routine `ecrire_image`**
  Ici on a opté pour un simple parcours de l'image avec une double boucle 'for'.
  Pour rendre l'affichage plus lisible, on a décidé de ne pas représenter le noir et le blanc chacun par un symbole différent. À la place on affiche un espace avec un fond coloré grâce aux séquences d'échappement ANSI.
- **Écriture de la routine `negatif_image`**
  Pour ne pas avoir d'effets de bord, on déclare une nouvelle image (neg_I) qui sera celle que l'on modifiera et retournera. On parcours l'image de départ (I) avec une double boucle 'for' et on inverse (avec l'opérateur 'not' (!)) la valeur de la case que l'on assigne a la case correspondante de 'neg_I'.
- **Écriture du programme de test `test_image.c`**
  On a choisi de tester les deux fonctions précédentes en créant une image de test (image_test) et en l'affichant. On affiche ensuite l'image négative (neg_I) de cette image.
- **Ajouts au fichier `Makefile`**
  On ajoute les règles de compilation nécessaires pour compiler le programme `test_image`.
- **Exécution du programme de test et vérification des résultats.**

### Tâche 2

#### Paquetage Geom2D

- **Définition des types `Point` et `Vecteur`**
- **Écriture de nombreuses routines** qui correspondent à des opérations mathématiques sur les points et les vecteurs
- **Écriture du programme de test `test_geom2D.c`**
  Ce fichier teste  chaque fonction individuellement en vérifiant si le résultat obtenu en l'applicant a un exemple d'argument correspond à celui attendu.
- **Ajouts au fichier `Makefile`**
  On ajoute les règles de compilation nécessaires pour compiler le module `test_geom2D`.
- **Exécution du programme de test et vérification des résultats.**

### Tâche 3

#### Partie 1

##### Paquetage calcul_contour

- **Ecriture de la procédure `calcul_contour`**
  On a choisi de faire une fonction qui prend en paramètre une image et le point de départ du contour et qui affiche à l'écran les points du contour.
  La procédure utilise un robot définit par sa position et son orientation.
  On a donc créé le type enuméré `orientation` qui contient 4 valeurs :

  - Nord
  - Est
  - Sud
  - Ouest

  On place le robot au point de départ puis tant qu'il ne revient pas au point de départ, on le fait se réorienter et avancer. On affiche le position du robot a chaque itération de la boucle.
  Il nous a fallu des fonctions intermédiaires :

  - `avancer`
    La fonction prend en paramètre un point et une orientation et renvoie le point obtenu en avancant tout droit avec cette orientation.
    On utilise un switch pour incrémenter ou décrementer la bonne coordonée dépendamment de l'orientation.
  - `tourner`
    La fonction prend en paramètre une orientation et un booleen qui décrit si il faut tourner a droite (vrai) ou a gauche (faux)
  - `trouver_pixel_départ`
    La fonction prend en paramètre une image et renvoie le premier pixel noir qu'elle trouve.
    Elle parcours l'image dans le sens de lecture (de gauche à droite et de haut en bas) avec un double for et retourne la position du premier pixel noir. Sinon, elle retourne (0;0).
  - `get_pixel_relatif`
    La fonction prend en paramètre une image, un point, une orientation et une direction (relative) et renvoie la valeur du pixel dans cette direction.
    On a donc du définir le type `direction` qui contient 4 valeurs:

    - Avant_gauche
    - Avant_droit
    - Arriere_gauche
    - Arriere_droit

  - `nouvelle_orientation`
    La fonction prend en paramètre une image, une position et une orientation et renvoie la nouvelle orientation du robot.
    On utilise la fonction `get_pixel_relatif` pour vérifier la couleur des pixels environnants. On calcule alors la nouvelle orientation avec la fonction `tourner`.

- **Ecriture du programme de test `test_calcul_contour.c`**
  La fonction `calcul_contour` est appelée sur l'image dont le nom est passé en argument pour que l'on puisse observer le résultat obtenu.
- **Ajouts au fichier `Makefile`**
  On ajoute les règles de compilation nécessaires pour compiler le programme `test_calcul_contour`.
- **Exécution du programme de test et vérification des résultats.**

#### Partie 2

##### Paquetage calcul_contour

Pour passer d'une fonction qui écrivait à l'écran le contour à une qui retournait une liste de points, on a d'abord changé le prototype de la fonction de :

```c
void calcul_contour(Image I, Point p_depart);
```

à :

```c
Liste_Point calcul_contour(Image I, Point p_depart);
```

Il a aussi fallut créer la liste de points que l'on allait retourner. Ensuite, au lieu dafficher à l'écran avec :

```c
printf("(%.0f,%.0f) ", p_robot.x, p_robot.y);
```

On ajoutait le point à la liste de cette façon :

```c
L = ajouter_element_liste_Point(L,p_robot);
```

On a aussi ajouté au paquetage liste_point la procédure :

```c
void ecrire_contour_fichier(Liste_Point L, char* nom_fichier);
```

Cette procédure parcours la liste de points donnée et ecrit dans un fichier `.contour` chacun des points.

Il a après fallu modifier légèrement le fichier test_contour pour s'adapter à ces changements.

### Tâche 4

#### Paquetage eps

- **Écriture de la routine `ecrire_fichier_eps`**
  La fonction prend en paramètre une image, ses dimensions (largeur et hauteur), le nom du fichier .eps dans lequel l'image doit être écrite au format Post Script Encapsulé, ainsi que le type de dessin (`STROKE` ou `FILL`).
  L'image y est écrite en parcourant, cellule par cellule, chaque point du contour précédemment extrait.

- **Ecriture du programme de test `test_eps.c`** Ce programme prend en argument une image et un mode de tracé ("stroke" ou "fill"). À partir d'un fichier image.pbm, ce programme crée le fichier image\_\<mode\>.eps représentant la même image avec le mode de tracé choisi.

- **Ajouts au fichier `Makefile`**
  On ajoute les règles de compilation nécessaires pour compiler le programme `test_eps`.
- **Exécution du programme de test et vérification des résultats.**

### Tâche 5

#### Partie 1

- **Ajout du type `Liste_Contour` et des types associés**
  Ce type permet la manipulation de listes de contours (listes de listes de points). Pour ce faire, nous avons également ajouté les types `Cellule_Liste_Contour` et `Tableau_Contour` contenant respectivement un contour sous forme de cellule de liste chainée, et une liste de contours sous forme de tableau.

- **Ajout de plusieurs fonctions élémentaires de manipulation de listes de contours**
  Afin de manipuler plus facilement ce nouveau type, nous nous sommes inspirés des fonctions de la Tâche 3 et avons ajouté des routines permettant de créer un élément, créer une liste, ajouter un élément à une liste, concaténer 2 listes et transformer une liste de contours en tableau de contours.

- **Mise à jour de la fonction `calcul_contour`** de la tâche 3 pour qu'elle retourne désormais une liste de contours. Pour ce faire, nous avons suivi l'algorithme consistant à créer une image masque (grâce à la fonction `creer_masque` de `calcul_contour.c`) que l'on parcourt à la recherche de nouveaux contours.

- **Mise à jour du programme de test `test_contour.c`**
  Ce programme prend en argument une image, en extrait tous les contours et les écrit dans le fichier .contour grâce à la fonction `ecrire_contours_fichier`, adaptation de la fonction de la tâche 3 à un ensemble de contours. Ce programme de test affiche à l'écran le nombre de contours et le nombre de segments.

- **Exécution du programme de test et vérification des résultats.**

#### Partie 2

- **Mise à jour de la fonction `ecrire_fichier_eps`** de la tâche 4 pour qu'elle prenne en argument une liste de contours au lieu d'un contour. Nous avons ainsi utilisé la commande `moveto` entre chaque contour (liste de points reliés par la commande `lineto`).

- **Mise à jour du programme de test `test_eps`** de la tâche 4 afin que l'ensemble des contours d'une image soit écrit au format EPS, en gardant toujours le choix sur le mode de tracé.

- **Exécution du programme de test et vérification des résultats.**

### Tâche 6

#### Partie 1

- **Ajout de la fonction `distance_point_segment`**
  Cette fonction utilise simplement la formule du cours.
- **Création du programme qui calcule la distance entre le segment et le point donné**
  Ce programme est très simple et attends 3 points en entrée standard et affiche la distance entre le segment formé des deux premiers points et le troisième.

#### Partie 2

- **Ajout de la fonction `simplification_douglas_peucker_segments`**
  Ici on a simplement appliqué l'algorithme du cours.
- **Création du programme `test_simplification`**
  Ce programme extrait les contours de l'image donnée, les simplifit en appelant la fonction `simplification_douglas_peucker_segments` sur chacun d'entre eux et les stockent dans une nouvelle liste de contours.
  Il y a ensuite des manipulations de chaines de caratères pour créer un nom pertinent pour les fichiers de sorties.
  Ensuite, on écrit les contours simplifiés dans des fichiers .contour et .eps.
  Enfin, on affiche à l'écran le nombre de contours et le nombre de segments.

### Tâche 7

#### Partie 1

- **Fonction `approx_bezier2`**
  
  On a simplement appliqué l'algorithme du cours auquel on a apporté quelques modifications.
  Au lieu de passer le contour complet et les indices de debut et de fin du contour etudié dans cet appel, on a décidé, pour des questions d'optimisations, de passer seulement le contour étudié dans cet appel.
- **Fonction `simplification_douglas_peucker_bezier2`**
  
  On a simplement appliqué l'algorithme du cours à l'exception de l'appel de `approx_bezier2` qui se fait sur un sous séquence (calculée avec la fonction `sous_sequence_points_liste`).
- **Fonction `sous_sequence_points_liste`**
  
  Cette fonction prends un liste de points et deux indices. Elle retourne la séquence contenue entre ces deux indices.

- **Fonctions `alpha_2` et `beta_2`**
  
  Simple copie des fonctions $\alpha(n)$ et $\beta(n)$ présentées dans le cours.
- **Fonction `ecrire_fichier_eps_bezier2`**
  
  La fonction convertit les courbes de Bézier de degré 2 en degré 3 (car le format eps n'accepte que des courbes de degré 3). Elle les écrit ensuite dans un fichier eps (en utilisant la commande `curveto`).

#### Partie 2

- **Fonction `approx_bezier3`**
  
  Ici on a procédé de la même façon que pour la partie 1 mais avec l'algorithme donné pour les courbes de Bézier de degré 3.

- **Fonction `simplification_douglas_peucker_bezier3`**
  
  De même pour cette fonction.

- **Fonction `ecrire_fichier_eps_bezier3`**
  
  Cette fonction est presque la même que `ecrire_fichier_eps_bezier2` au détail près qu'il n'y a pas besoin de procéder à une élévation de degré car on a déjà des courbes de degré 3.

- **Fonctions `alpha_3`, `beta_3`, `lambda_3` et `gamma_3`**
  
  Simple copie des fonctions $\alpha(n)$, $\beta(n)$, $\lambda(n)$ et $\gamma(k,n)$ présentées dans le cours.
  
### Tâche 8

Quand nous avons commencé à tester les images de la tâche 8, on s'est vite heurté à des problèmes. Appliquer la simplification sur des trop grosses images faisait planter le programme. En effet, la quantité de mémoire RAM utilisée devenait si grande qu'elle dépassait ce qui était disponible sur nos machines.
Le problème vient du fait qu'à chaque appel récursif, on créait un nouveau tableau à partir du contour.

Notre première piste a été de donner à chaque appel récursif un contour déjà tronqué plutôt que de donner le contour entier et les indice de début et de fin. Cela a réduit un peu le nombre d'opérations mais n'a pas suffisamment affecté l'usage de la mémoire RAM.

La solution finale a été, au lieu de passer en paramètre un contour entier, de passer un tableau de points qui correspond uniquement à la partie du contour à simplifier pour cet appel.

Utiliser un tableau nous a alors permis d'utiliser le même espace mémoire a chaque appel. En effet pour passer un tableau de points, on créé un objet tableau (structure qui contient un pointeur vers le début du tableau et un int qui donne la longueur du tableau => cette structure prends peu de place), et on décale le pointeur de départ ou on réduit la taille pour passer seulement une partie du tableau sans avoir à recréer un espace pour tout les points.
Cette technique permet de diminuer drastiquement l'utilisation de mémoire RAM.
Ainsi le programme peux fonctionner correctement et vite.

## Manuel d'utilisation

### Compilation

Pour compiler le projet, il suffit de se placer dans le dossier `Version_finale` (ou une tache spécifique) et d'exécuter la commande `make`.

### Dépendances

![graph des dépendances du programme principal](Readme_files/Dependances_main.png)

### Exécution

- **Tâche 5**

  Pour convertir une image pbm en eps, il faut appeler la commande :

  > ./test_eps <chemin_de_l'image_de_départ> <mode_de_tracé>

  avec <mode_de_tracé> :

  - "stroke" pour avoir seul le tracé des contours
  - "fill" pour avoir le mode remplissage

  L'image ainsi produite se trouvera dans le dossier `IMAGES` sous le nom `<nom_de_l'image_de_départ>_<mode_de_tracé>.eps`.

  <br>

  Pour extraire tous les contours d'une image et les sauvegarder dans un fichier texte, il faut exécuter la commande :
   > ./test_contour <chemin_de_l'image_de_départ>

  L'image ainsi produite se trouvera dans le dossier `IMAGES` sous le nom `<nom_de_l'image_de_départ>.contour` et seront affichés à l'écran le nombre de contours et de segments.

- **Tâche 6**

  Pour simplifier une image, il faut appeler la commande :

  > ./test_simplifications <chemin_de_l'image_de_départ> <distance_seuil>

  avec **<distance_seuil>** un `double` positif.
  L'image ainsi produite se trouvera dans le dossier `Sortie_eps` sous le nom : `<nom_de_l'image_de_départ>_sdp_segments_d=<distance_seuil>.eps`
  (sdp = simplification de Douglas-Peucker)

- **Version finale / Tâche 7 / Tâche 8**

  Pour simplifier une image, il faut appeler la commande :

  > ./main <chemin_de_l'image_de_départ> <distance_seuil> <degré>

  avec **<distance_seuil>** un `double` positif ou nul et **<degré>** :

  - 0 pour l'image originale
  - 1 pour simplification par segment
  - 2 pour simplification par courbes de bézier de degré 2
  - 3 pour simplification par courbes de bézier de degré 3

  L'image ainsi produite se trouvera dans le dossier `Sortie_eps` sous le nom : `<nom_de_l'image_de_départ>_sdp_<degré>_d=<distance_seuil>.eps`
  (sdp = simplification de Douglas-Peucker)
  avec <degré> :

  - segments
  - beziers2
  - beziers3

## Suivi du projet

### Diagramme de Gantt

![Diagramme de Gantt](Readme_files/Diagramme_de_Gantt.png)

### Journal de bord

![Journal de bord](Readme_files/Journal_de_Bord.png)

## Auteurs

- **Yann Letourneur**
- **Gwendal Trehin**
