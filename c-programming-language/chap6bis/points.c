#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

struct point makepoint(int x, int y) {
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
};

struct point addpoint(struct point p1, struct point p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

int point_in_rect(struct point p, struct rect r) {
    return p.x >= r.pt1.x && p.x <= r.pt2.x && p.y >= r.pt1.y && p.y <= r.pt2.y;
}

struct rect canonrect(struct rect r) {
    struct rect temp;
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

int main() {
    struct rect screen;
    struct point middle;
    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(300, 400);
    middle = makepoint(
        (screen.pt1.x + screen.pt2.x)/2,
        (screen.pt1.y + screen.pt2.y)/2
    );
    printf("middle: (%d,%d)\n", middle.x, middle.y);

    struct point p3 = addpoint(screen.pt1, screen.pt2);
    printf("p3: (%d,%d)\n", p3.x, p3.y);

    struct point p1 = {-1, -2};
    printf(
        "(%d,%d) in screen: %s\n", 
        p1.x,
        p1.y,
        point_in_rect(p1, screen) == 1 ? "yes" : "no"
    );
    printf(
        "(%d,%d) in screen: %s\n",
        middle.x,
        middle.y,
        point_in_rect(middle, screen) == 1 ? "yes" : "no"
    );
    struct point origin, *point_ptr;
    point_ptr = &origin;
    printf("origin is (%d,%d)\n", point_ptr->x, point_ptr->y);
    return 0;
}
