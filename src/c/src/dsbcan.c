#include <stdio.h>
#include "../lib/point.h"
#include "../lib/cluster.h"
#include "../lib/cloud.h"
#include "../lib/common.h"
#include "../lib/inout.h"
#include "../lib/test.h"

float RADIUS = 0;
int MIN_PTS = 0;

void dbscan(cloud_t* cloud){
    point_t* point = NULL;
    point_t* current = cloud_first_point(cloud);
    point_t* pseudo_cluster[MIN_PTS];
    cluster_t* cluster = NULL;
    int i = 0;
    int j = 0;

    while(current){
        pseudo_cluster[0] = current;
        i = 1;
        point = cloud_first_point(cloud);
        while((point = next_point(point)) && i <= MIN_PTS) {
            if (is_close(current, point)) {
                pseudo_cluster[i] = point;
                i++;
            }
        }
        if(i <= MIN_PTS){
            current = next_point(current);
            for(j=0; j<i; j++)
                pseudo_cluster[j] = NULL;
        }
        else{
            add_cluster(cloud);
            cluster = cloud_last_cluster(cloud);
            transfert_to_cluster(cloud, cluster, pseudo_cluster, MIN_PTS);
            spread_last_cluster(cloud);
            current = cloud_first_point(cloud);
        }
    }
    cloud_noise(cloud);
}

int main(int argc, char** argv){
    if(argc < 4){
        my_fprintf(stdout, BLUE, BOLD, TRUE, "usage: ./main path_to_data output_filename radius minPoint");
        exit(1);
    }

    RADIUS = fabs(atof(argv[2]));
    MIN_PTS = atoi(argv[3]);
    if(MIN_PTS < 1){
        my_fprintf(stdout, GREEN, NONE, TRUE, "MIN_PTS sets to 1 instead of %s", argv[3]);
        MIN_PTS = 1;
    }

    cloud_t* cloud = read_data(argv[1]);
    dbscan(cloud);

    char* filename = extract_filename(argv[1], "dsbcan");
    write_output(filename, cloud);
    make_stats(filename, cloud);
    free_cloud(cloud);
    free(filename);
    return 0;
}
