#ifndef __SIMPLIFICATION_H__
#define __SIMPLIFICATION_H__

#include "liste_point.h"

Contour simplification_douglas_peucker_segments(Contour Cont, int j1, int j2, double d);

#endif