#include <stdio.h>
#include <math.h>


int main(int argc, char *argv[]) {
    struct point {  /* point is the tag */
        int x;  /* member */
        int y;  /* member */
    };

    struct rect {
        struct point pt1;
        struct point pt2;
    };

    struct point pt = {320, 200};
    printf("pt.x = %d, pt.y = %d\n", pt.x, pt.y);

    double dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);
    printf("distance between origin and pt: %f\n", dist);

    struct point pt2 = {500, 500};
    struct rect screen = {pt, pt2};
    
    return 0;
}
