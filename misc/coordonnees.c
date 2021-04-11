#include <stdio.h>
#include "coordonnees.h"

int main(int argc, char *argv[]) {

    Point point;
    printf("Please enter coordinates of a point : ");
    scanf("%d%d", &point.x, &point.y);
    printf("x : %d, y : %d\n", point.x, point.y);
    
    return 0;
}


