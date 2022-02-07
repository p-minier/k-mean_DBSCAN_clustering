#ifndef POINT_H_
#define POINT_H_
#include <math.h>
#include "common.h"

typedef struct Point{
    float* coord;
    char* answer;
    void* next;
}point_t;

// alloc & free
point_t* new_point(float* coord, char* answear);
void free_point(point_t*);

// public getters
float* point_all_coord(point_t*);
const float point_coord(point_t*, int);
char* point_answer(point_t*);
point_t* next_point(point_t*);

// public setter
void set_next_point(point_t*, point_t*);

// distance evaluation
float d_pointPoint(point_t*, point_t*);
float d_pointFloat(point_t*, float*);
float d_floatFloat(float*, float*);
int is_close(point_t*, point_t*);

#endif