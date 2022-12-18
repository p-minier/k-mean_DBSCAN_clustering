#include "../lib/cluster.h"

extern const int DIM;

unsigned int cluster_nb_points(cluster_t* c){return c->nb_points;}
point_t* cluster_first_point(cluster_t* c){return c->first_point;}
point_t* cluster_last_point(cluster_t* c){return c->last_point;}
cluster_t* next_cluster(cluster_t* c){return c->next;}

void set_cluster_first_point(cluster_t* c, point_t* p){c->first_point=p;}
void set_cluster_last_point(cluster_t* c, point_t* p){c->last_point=p;}
void set_next_cluster(cluster_t* c, cluster_t* next){c->next=next;}

cluster_t* new_cluster(unsigned int id){
    cluster_t* c = malloc(sizeof(cluster_t));
    c->nb_points = 0;
    set_cluster_last_point(c, NULL);
    set_cluster_first_point(c, NULL);
    set_next_cluster(c, NULL);
    return c;
}

void free_cluster(cluster_t* c){
    point_t* p = NULL;
    while(p = cluster_first_point(c)){
        set_cluster_first_point(c, next_point(p));
        free_point(p);
    }
    free(c);
}

void add_point(cluster_t* c, point_t* p){
    c->nb_points++;
    if(cluster_first_point(c)){
        set_next_point(cluster_last_point(c), p);
        set_cluster_last_point(c, p);
    }
    else{
        set_cluster_first_point(c, p);
        set_cluster_last_point(c, p);
    }
}