#ifndef CLUSTER_H_
#define CLUSTER_H_
#include "point.h"

typedef struct Cluster{
    unsigned int nb_points;
    point_t* first_point;
    point_t* last_point;
    void* next;
}cluster_t;

// alloc & free
cluster_t* new_cluster(unsigned int id);
void free_cluster(cluster_t* c);

// public getters
unsigned int cluster_nb_points(cluster_t* c);
point_t* cluster_first_point(cluster_t* c);
point_t* cluster_last_point(cluster_t* c);
cluster_t* next_cluster(cluster_t* c);

// public setters
void set_next_cluster(cluster_t* c, cluster_t* next);
void add_point(cluster_t* c, point_t* p);

#endif