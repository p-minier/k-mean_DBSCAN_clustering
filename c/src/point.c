#include "../lib/point.h"
extern const float RADIUS;
extern const int DIM;

point_t* new_point(float* coord, char* answer){
    point_t* p = malloc(sizeof(point_t));
    p->coord = coord;
    p->answer = malloc(strlen(answer)+2);
    memcpy(p->answer, answer, strlen(answer)+1);
    p->next = NULL;
    return p;
}

void free_point(point_t* p){
    free(p->coord);
    free(p->answer);
    free(p);
}

float* point_all_coord(point_t* p){return p->coord;}

const float point_coord(point_t* p, int i){
    if(i > DIM){
        printf("[point_coord]: dimension %d asked\n", i+1);
        abort();
    }
    return p->coord[i];
}

char* point_answer(point_t* p){return p->answer;}

point_t* next_point(point_t* p) {return p->next;}
void set_next_point(point_t* p, point_t* next){p->next = next;}

float d_pointPoint(point_t* p1, point_t* p2){
    return d_floatFloat(p1->coord, p2->coord);
}

float d_pointFloat(point_t* p, float* coord){
    return d_floatFloat(p->coord, coord);
}

float d_floatFloat(float* coord1, float* coord2){
    float d = 0;
    for(int i = 0; i < DIM-1; i++)
        d += pow(coord1[i] - coord2[i], 2);

    return pow(d, 0.5);
}

int is_close(point_t* p1, point_t* p2){
    return d_pointPoint(p1, p2) <= RADIUS;
}