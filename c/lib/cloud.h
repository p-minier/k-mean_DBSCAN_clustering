#ifndef CLOUD_H_
#define CLOUD_H_

#include "common.h"
#include "cluster.h"

typedef struct Cloud{
    unsigned int dim;
    int border[4];
    unsigned int nb_points;
    unsigned int nb_clusters;
    unsigned int is_noise;
    point_t* first_point;
    cluster_t* first_cluster;
    cluster_t* last_cluster;
}cloud_t;

// alloc & free
cloud_t* new_cloud(int dim);
void free_cloud(cloud_t* c);

// public getters
unsigned int cloud_dim(cloud_t* c);
int* cloud_border(cloud_t* c);
unsigned int nb_points(cloud_t* c);
unsigned int nb_clusters(cloud_t* c);
unsigned int is_noise(cloud_t* c);
point_t* cloud_first_point(cloud_t* c);
point_t* cloud_ranked_point(cloud_t* c, int n);
cluster_t* cloud_first_cluster(cloud_t* c);
cluster_t* cloud_last_cluster(cloud_t* c);

// cloud monitoring
void load_point(cloud_t* c, float* coord, char* answear);
void add_cluster(cloud_t* c);
void cloud_noise(cloud_t* c);

// cluster monitoring
void transfert_to_cluster(cloud_t* cloud, cluster_t* cluster, point_t* tab[], int n);
void spread_last_cluster(cloud_t* cloud);

#endif