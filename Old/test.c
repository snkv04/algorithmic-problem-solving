#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point {
    int x, y;
};

int main() {
    long myLong = 123456789012L;
    long myLong2 = 123456789012;
    printf("%ld\n", myLong);
    printf("%ld\n", myLong2);

    // struct Point p;
    // p.x = 7;
    // p.y = 8;

    struct Point** points = (struct Point**) (calloc(5, sizeof(struct Point*)));
    for (int i = 0; i <= 4; i++) {
        points[i] = (struct Point*) calloc(1, sizeof(struct Point));
        points[i]->x = 2*i;
        points[i]->y = 2*i+1;
    }

    for (int i = 0; i <= 4; i++) {
        printf("(x=%d, y=%d)\n", points[i]->x, points[i]->y);
    }

    points = realloc(points, 10*sizeof(struct Point*));
    for (int i = 0; i <= 4; i++) {
        printf("(x=%d, y=%d)\n", points[i]->x, points[i]->y);
    }

    return 0;
}