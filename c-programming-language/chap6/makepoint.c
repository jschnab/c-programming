#include <stdio.h>


#define XMAX 320
#define YMAX 200
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))


struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};


/* make a point from x and y components */
struct point makepoint(int x, int y) {
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
};

/* add two points */
struct point addpoint(struct point p1, struct point p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
};

/* return 1 if p in r, 0 if not */
int pt_in_rect(struct point p, struct rect r) {
    return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
};

/* canonicalize coordinates of rectanble */
struct rect canon_rect(struct rect r) {
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
};

struct rect screen;
struct rect middle;


int main(int argc, char *argv[]) {
    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    struct point middle = makepoint(
        (screen.pt1.x + screen.pt2.x) / 2,
        (screen.pt1.y + screen.pt2.y) / 2
    );
    printf("middle.x = %d, middle.y = %d\n", middle.x, middle.y);
    return 0;
}
