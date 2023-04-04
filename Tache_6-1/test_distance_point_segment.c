#include <stdio.h>
#include "geom2d.h"

int main()
{
    Point P, A, B;
    printf("Point P :\n-->\t");
    scanf("%lf %lf", &P.x, &P.y);
    printf("Point A :\n-->\t");
    scanf("%lf %lf", &A.x, &A.y);
    printf("Point B :\n-->\t");
    scanf("%lf %lf", &B.x, &B.y);
    printf("Distance entre P et AB : %lf\n", distance_point_segment(P, A, B));
}