#include <stdio.h>
#include <time.h>
#include "../lib/point.h"
#include "../lib/cluster.h"
#include "../lib/cloud.h"
#include "../lib/common.h"
#include "../lib/inout.h"
#include "../lib/test.h"

float RADIUS = 0;

void kmean(cloud_t* cloud, const int K){
    int i, j, k;
    float dist, tmp_dist;
    point_t* point_loop, *point;
    cluster_t* clusters[K];
    point_t* centroides[K];
    const int NB_POINTS = nb_points(cloud);
    float proba[NB_POINTS];
    float max_proba;

/*
    // initialisation aléatoire des clusters
    for(i = 0; i < K; i++){
        centroides[i] = cloud_ranked_point(cloud, clock() % (NB_POINTS-i));
    }

*/

// début de kmean ++
    for(i=0; i < NB_POINTS; i++){
        proba[i] = 0;
    }

    centroides[0] = cloud_ranked_point(cloud, clock() % NB_POINTS);

    float max_distance;
    point = NULL;
    for(k = 1; k < K; k++){
        max_distance = 0;
        point_loop = cloud_first_point(cloud);
        while(point_loop){
            dist = 0;
            for(i = 0; i < k; i++){
                dist += d_pointPoint(point_loop, centroides[i]);
                if(dist > max_distance){
                    max_distance = dist;
                    centroides[k] = point_loop;
                }
            }
            point_loop = next_point(point_loop);
        }
    }

    max_distance = 0;
    point_loop = cloud_first_point(cloud);
    while(point_loop){
        dist = 0;
        for(i = 1; i < K; i++){
            dist += d_pointPoint(point_loop, centroides[i]);
            if(dist > max_distance){
                max_distance = dist;
                centroides[0] = point_loop;
            }
        }
        point_loop = next_point(point_loop);
    }
// fin de kmean ++

    for(k = 0; k < K; k++){
        add_cluster(cloud);
        clusters[k] = cloud_last_cluster(cloud);
        transfert_to_cluster(cloud, clusters[k], &centroides[k], 1);
    }


    point_loop = cloud_first_point(cloud);
    while(point_loop){
        j = 0;
        tmp_dist = 0;
        dist = 1.0/0.0;
        for(i = 0; i < K; i++){
            tmp_dist = d_pointPoint(point_loop, centroides[i]);
            if(tmp_dist < dist){
                dist = tmp_dist;
                j = i;
            }
        }
        point = point_loop;
        point_loop = next_point(point);
        transfert_to_cluster(cloud, clusters[j], &point, 1);
    }
}

int main(int argc, char** argv){
    if(argc < 3){
        my_fprintf(stdout, BLUE, BOLD, TRUE, "usage: ./main path_to_data output_filename number_of_cluster");
        exit(1);
    }

    int K = fabs(atof(argv[2]));
    K = !K ? 1:K;

    cloud_t* cloud = read_data(argv[1]);
    kmean(cloud, K);

    char* filename = extract_filename(argv[1], "kmean");
    write_output(filename, cloud);
    make_stats(filename, cloud);
    free_cloud(cloud);
    free(filename);
    return 0;
}
