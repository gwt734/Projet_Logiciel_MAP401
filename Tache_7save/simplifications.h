#ifndef __SIMPLIFICATION_H__
#define __SIMPLIFICATION_H__

#include "liste_point.h"

/*
 * Simplification de Douglas-Peucker

 * Cont: contour à simplifier
 * j1: indice du premier point du contour à simplifier
 * j2: indice du dernier point du contour à simplifier
 * d: distance maximale entre le point et la droite
 * 
 * retourne: le contour simplifié
 */
Contour simplification_douglas_peucker(Contour Cont, int j1, int j2, double d);

/*
 * Coefficient alpha de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 2

 * n: nombre de points du contour à simplifier

 * retourne: le coefficient alpha
 */
double alpha_2(double n);

/*
 * Coefficient beta de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 2

 * n: nombre de points du contour à simplifier

 * retourne: le coefficient beta
 */
double beta_2(double n);

/*
 * Approximation d'un contour par une courbe de Bézier de degré 2

 * C: contour à approximer

 * retourne: la courbe de Bézier approximée
 */
Bezier2 approx_bezier2(Contour C);

/*
 * Sous-séquence d'un contour

 * CONT: contour
 * j1: indice du premier point de la séquence à extraire
 * j2: indice du dernier point de la séquence à extraire
 * 
 * retourne: la sous séquence
 */
Contour sous_sequence_points_liste(Contour CONT, int j1, int j2);

/*
 * Simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 2

 * CONT: contour à simplifier
 * j1: indice du premier point du contour à simplifier
 * j2: indice du dernier point du contour à simplifier
 * d: distance maximale entre le point et la droite
 * 
 * retourne: le contour simplifié
 */
Contour simplification_douglas_peucker_bezier2(Contour CONT, int j1, int j2, double d);

/*
 * Coefficient alpha de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 * 
 * n: nombre de points du contour à simplifier
 * 
 * retourne: le coefficient alpha
 */
double alpha_3(int n);

/*
 * Coefficient beta de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 * 
 * n: nombre de points du contour à simplifier
 * 
 * retourne: le coefficient beta
 */
double beta_3(int n);

/*
 * Coefficient lambda de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 * 
 * n: nombre de points du contour à simplifier
 * 
 * retourne: le coefficient lambda
 */
double lambda_3(int n);

/*
 * Coefficient gamma de la méthode de simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 * 
 * k: indice du point du contour à simplifier
 * n: nombre de points du contour à simplifier
 * 
 * retourne: le coefficient gamma
 */
double gamma_3(int k, int n);

/*
 * Approximation d'un contour par une courbe de Bézier de degré 3
 * 
 * C: contour à approximer
 * 
 * retourne: la courbe de Bézier approximée
 */
Bezier3 approx_bezier3(Contour C);

/*
 * Simplification de Douglas-Peucker avec approximation par courbe de Bézier de degré 3
 * 
 * CONT: contour à simplifier
 * j1: indice du premier point du contour à simplifier
 * j2: indice du dernier point du contour à simplifier
 * d: distance maximale entre le point et la droite
 * 
 * retourne: le contour simplifié
 */
Contour simplification_douglas_peucker_bezier3(Contour CONT, int j1, int j2, double d);

#endif
