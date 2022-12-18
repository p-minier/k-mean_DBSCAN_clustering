#include "../lib/cloud.h"
#include "../lib/cluster.h"
#include "../lib/point.h"

void print_cloud(cloud_t* cloud){
    cluster_t* cluster = NULL;
    point_t* point = NULL;
    int dim = cloud_dim(cloud);
    int i;
    printf("Start test\n");
    printf("In clusters:\n");

    while(cluster = cloud_first_cluster(cloud)){
        point = cluster_first_point(cluster);
        while(point){
            printf("(");
            for(i = 0; i < dim; i++){
                printf("%.1f,", point_coord(point, i));
            }
            printf(")\n");
            point = next_point(point);
        }
    }

    printf("\n\nNon affected:\n");
    point = cloud_first_point(cloud);
    while(point){
        printf("(");
        for(i = 0; i < dim-1; i++){
            printf("%.1f, ", point_coord(point, i));
        }
        printf("%s)\n", point_answer(point));
        point = next_point(point);
    }
}