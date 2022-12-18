#include "../lib/cloud.h"

cloud_t* new_cloud(int dim){
    cloud_t* c = malloc(sizeof(cloud_t));
    c->dim = dim;
    memset(c->border, 0, 4);
    c->nb_points = 0;
    c->nb_clusters = 0;
    c->is_noise = 0;
    c->first_point = NULL;
    c->first_cluster = NULL;
    c->last_cluster  = NULL;
}
void free_cloud(cloud_t* cloud){
    cluster_t* cluster = cloud_first_cluster(cloud);

    do{
        cloud->first_cluster = next_cluster(cluster);
        free_cluster(cluster);
    }while(cluster = cloud_first_cluster(cloud));

    free(cloud);
}

unsigned int cloud_dim(cloud_t* c)        {return c->dim;}
int* cloud_border(cloud_t* c)             {return c->border;}
unsigned int nb_points(cloud_t* c)        {return c->nb_points;}
unsigned int nb_clusters(cloud_t* c)      {return c->nb_clusters;}
unsigned int is_noise(cloud_t* c)         {return c->is_noise;}
point_t* cloud_first_point(cloud_t* c)    {return c->first_point;}
cluster_t* cloud_first_cluster(cloud_t* c){return c->first_cluster;}
cluster_t* cloud_last_cluster(cloud_t* c) {return c->last_cluster;}

point_t* cloud_ranked_point(cloud_t* c, int n){
    point_t* point = cloud_first_point(c);
    int i = 0;
    while(point && i < n){
        point = next_point(point);
        i++;
    }
    return point;
}

void set_last_cluster(cloud_t* cloud, cluster_t* cluster){cloud->last_cluster = cluster;}
void set_first_point(cloud_t* c, point_t* p){c->first_point = p;}

void update_border(cloud_t*c, float* coord){
    if     (c->border[0] > coord[0]) c->border[0] = coord[0];
    else if(c->border[2] < coord[0]) c->border[2] = coord[0];
    if     (c->border[1] > coord[1]) c->border[1] = coord[1];
    else if(c->border[3] < coord[1]) c->border[3] = coord[1];
}

point_t* current = NULL;

void load_point(cloud_t* c, float* coord, char* answear){
    c->nb_points++;
    point_t* p = new_point(coord, answear);
    if(current){
        set_next_point(current, p);
        update_border(c, coord);
    }
    else{
        c->border[0] = coord[0];
        c->border[1] = coord[1];
        c->border[2] = coord[0];
        c->border[3] = coord[1];
        set_first_point(c, p);
    }
    current = p;
}
void add_cluster(cloud_t* cloud){
    cloud->nb_clusters++;
    cluster_t* cluster = new_cluster(nb_clusters(cloud));
    if(!cloud->first_cluster){
        cloud->first_cluster = cluster;
        cloud->last_cluster = cluster;
    }
    else{
        set_next_cluster(cloud_last_cluster(cloud), cluster);
        set_next_point(cluster_last_point(cloud_last_cluster(cloud)), NULL);
        set_last_cluster(cloud, cluster);
    }
}
void cloud_noise(cloud_t* c){
    point_t* p = cloud_first_point(c);
    cluster_t* noise = new_cluster(0);
    c->is_noise = 1;
    if(p){
        do{
            add_point(noise, p);
        }while(p = next_point(p));
    }
    else{
    }
    set_next_cluster(noise, cloud_first_cluster(c));
    if (cloud_last_cluster(c))
    set_next_point(cluster_last_point(cloud_last_cluster(c)), NULL);
    c->first_cluster = noise;
}

void transfert_to_cluster(cloud_t* cloud, cluster_t* cluster, point_t* tab[], int n){
    point_t* point = cloud_first_point(cloud);
    point_t* previous = NULL;
    int i = 0;
    while(point && i < n){
        if(point == tab[i]){
            if(!previous){
                set_first_point(cloud, next_point(point));
                set_next_point(point, NULL);
                add_point(cluster, point);

                point = cloud_first_point(cloud);
                previous = NULL;
            }
            else if(!next_point(point)){
                set_next_point(previous, NULL);
                add_point(cluster, point);
            }
            else{
                set_next_point(previous, next_point(point));
                set_next_point(point, NULL);
                add_point(cluster, point);

                point = next_point(previous);
            }
            i++;
        }
        else{
            previous = point;
            point = next_point(point);
        }
    }
}

void spread_last_cluster(cloud_t* cloud){
    cluster_t* cluster = cloud_last_cluster(cloud);
    point_t* current = cluster_first_point(cluster);
    point_t* point = NULL;
    point_t* cpy_p = NULL;
    while(current){
        point = cloud_first_point(cloud);
        while(point){
            cpy_p = point;
            point = next_point(point);
            if(is_close(cpy_p, current)){
                transfert_to_cluster(cloud, cluster, &cpy_p, 1);
            }
        }
        current = next_point(current);
    }
}