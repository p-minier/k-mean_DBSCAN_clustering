#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef struct Point{
    int id;
    float x;
    float y;
} point_t;

float distance(float(*dst)(), ...){
    va_list args;
    va_start(args, dst);
    float res = (*dst)(1, args);
    va_end(args);
    return res;
}

float floatFloat(float x1, float y1, float x2, float y2){
    return pow(pow(x1 - x2, 2) + pow(y1 - y2, 2), 0.5);
}

float pointFloat(point_t* p, float x, float y){
    return floatFloat(p->x, p->y, x, y);
}

float pointPoint(void* p1, void* p2){
    return floatFloat(((point_t*)p1)->x, ((point_t*)p1)->y, ((point_t*)p2)->x, ((point_t*)p2)->y);
}

int main(int argc, char const *argv[]) {
    (*printf)("Hello world !\n");

    float x1 = 1.35; float y1 = 2.54;
    float x2 = 3.42; float y2 = 1.32;

    point_t p1 = {0, x1, y1};
    point_t p2 = {1, x2, y2};

    //printf("floatFloat: %2.f\n", distance(floatFloat, &x1, &y1, &x2, &y2));
    //printf("pointFloat: %2.f\n", distance(pointFloat, &p1, &x2, &y2));
    //printf("pointPoint: %.3f\n", distance(pointPoint, &p1, &p2));

    printf("floatFloat: %.3f\n", floatFloat(x1, y1, x2, y2));
    printf("pointFloat: %.3f\n", pointFloat(&p1, x2, y2));
    printf("pointPoint: %.3f\n", pointPoint(&p1, &p2));

    return 0;
}













