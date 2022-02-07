#include <unistd.h>
#include <fcntl.h>
#include "../lib/inout.h"

extern const float RADIUS;
int DIM = 0;

int max_c = 9;
char color[][9] = {"black", "blue", "red", "green", "purple", "fuchsia", "navy", "aqua", "maroon", "yellow"};

cloud_t* read_data(char* path){
    FILE* data = fopen(path, "r");
    if(!data){
        my_fprintf(stdout, RED, NONE, TRUE, "%s n'existe pas", path);
        exit(1);
    }
    char line[MAX_LINE];
    char* buffer = NULL;
    char** axe = NULL;
    int i;

    // dimension des points
    unsigned int dim = 1;
    int car = -1;
    fgets(line, MAX_LINE, data);
    for(dim; line[dim+car]; line[dim+car]==',' ? dim++ : car++);
    DIM = dim;

    // allocation du nuage de points
    cloud_t* cloud = new_cloud(dim);

    // remplissage du nuage
    while(fgets(line, MAX_LINE, data)){
        buffer = strtok(line, ",");
        float* coord = malloc((dim-1) * sizeof(float));
        for(i = 0; i < dim-1; i++){
            *(coord+i) = atof(buffer);
            buffer = strtok(NULL, ",");
        }
        load_point(cloud, coord, buffer);
    }


    fclose(data);
    return cloud;
}

char* extract_filename(char* path, char* algo){
    char* token, *last;
    last = token = strtok(path, "/");
    for(;(token = strtok(NULL, "/")) != NULL; last = token);
    char* filename = malloc(strlen(last) + 1 + strlen(algo) + 1);
    sprintf(filename, "%s/%s", algo, last);
    return filename;
}

int redirection(char* filename, char* extension){
    // création du nom de fichier
    char* path = malloc(strlen("output/") + strlen(filename) -3 + strlen(extension) + 1);
    sprintf(path, "output/%s", filename);
    memcpy(path+strlen(path)-3, extension, strlen(extension));

    remove(path);
    int pfd = open(path, O_WRONLY | O_CREAT, 0777);
    free(path);
    fflush(stdout);
    int saved = dup(STDOUT_FILENO);

    close(STDOUT_FILENO);
    dup(pfd);
    close(pfd);

    return saved;
}

void restauration(int saved_fd){
    fflush(stdout);
    dup2(saved_fd, STDOUT_FILENO);
    close(saved_fd);
}

void write_output(char* path, cloud_t* cloud){
    cluster_t* cluster = NULL;
    point_t* point = NULL;
    int i, j;

    // calcul de la dimension de la boite
    int* border = cloud_border(cloud);
    int margin  = 2.5;
    int w = border[2] - border[0] + 2*margin; // marge pour ne pas avoir
    int h = border[3] - border[1] + 2*margin; // de points collés au bord

    int p_size   = max(1, SCALE * (w+h)/200); // diviser par 2*nb_point
    int p_radius = RADIUS * SCALE;

    // redirection vers un fichier svg
    int saved = redirection(path, "svg");

    printf("<svg width=\"%d\" height=\"%d\" transform=\"translate(%d %d)\">\n", w*SCALE, h*SCALE, (margin-border[0])*SCALE, (margin-border[1])*SCALE);
    printf("<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"white\"/>\n", (border[0]-margin)*SCALE, (border[1]-margin)*SCALE, w*SCALE, h*SCALE);
    i = is_noise(cloud) == 1 ? -1:0;
    cluster = cloud_first_cluster(cloud);
    do{
        if(i >= 0 && PRINT_RADIUS){
            printf("<g id=\"cluster-area-%d\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.04\">\n", i, color[i % max_c + 1], color[i % max_c + 1]);
            point = cluster_first_point(cluster);
            while(point){
                printf("\t<circle cx=\"%.0f\" cy=\"%.0f\" r=\"%d\"/>\n", point_coord(point, 0)*SCALE, point_coord(point, 1)*SCALE, p_radius);
                point = next_point(point);
            }
            printf("</g>\n");
        }
        printf("<g id=\"cluster-%d\" fill=\"%s\">\n", i, color[i % max_c + 1]);
        point = cluster_first_point(cluster);
        while(point){
            printf("\t<circle cx=\"%.0f\" cy=\"%.0f\" r=\"%d\"/>\n", point_coord(point, 0)*SCALE, point_coord(point, 1)*SCALE, p_size);
            point = next_point(point);
        }
        printf("</g>\n");
        i++;
    }while(cluster = next_cluster(cluster));

    printf("</svg>");

    restauration(saved);
}

void make_stats(char* path, cloud_t* cloud){
    int nb_cluster = nb_clusters(cloud);
    int i, j;
    float balance[nb_cluster][DIM-1];
    float tightness[nb_cluster];
    int N_cluster_points = nb_points(cloud)-cluster_nb_points(cloud_first_cluster(cloud));
    float a[N_cluster_points];
    float b[N_cluster_points];
    float s[N_cluster_points];
    point_t* point = NULL;
    point_t* point_2 = NULL;
    cluster_t* cluster = NULL;
    cluster_t* cluster_2 = NULL;
    float homogeneity = 0, separation = 0, score_DB = 0;

    float sum_x, sum_y, sum, b_tmp = 0;
    for (i = 0; i < nb_cluster; i++){
        tightness[i] = 0;
        for(j = 0; j < DIM-1; j++)
            balance[i][j] = 0;
    }
    for(i = 0; i < N_cluster_points; i++){
        a[i] = 0;
        b[i] = 0;
        s[i] = 0;
    }

    i = j = 0;
    cluster = cloud_first_cluster(cloud);
    if(is_noise(cloud)) cluster = next_cluster(cluster);
    do{
        point = cluster_first_point(cluster);
        N_cluster_points = cluster_nb_points(cluster);

        // balance points evaluation
        sum_x = sum_y = 0;
        while(point){
            for(j = 0; j < DIM-1; j++){
                balance[i][j] += point_coord(point, j);
            }
            point = next_point(point);
        }
        for(j = 0; j < DIM-1; j++){
            balance[i][j] /= N_cluster_points;
        }

        // tightness evaluation
        tightness[i] = 0;
        point = cluster_first_point(cluster);
        while(point){
            tightness[i] += d_pointFloat(point, balance[i]);
            point = next_point(point);
        }
        tightness[i] /= N_cluster_points;

        // a and b coeff evaluation
        j = 0;
        point = cluster_first_point(cluster);
        do{
            // a coeff
            point_2 = cluster_first_point(cluster);
            sum = 0;
            do{
                sum += d_pointPoint(point, point_2);
            }while(point_2 = next_point(point_2));
            a[j] = sum/(N_cluster_points-1);
            // b coeff
            cluster_2 = cloud_first_cluster(cloud);
            b_tmp = 0;
            b[j] = 0;
            while(cluster_2 = next_cluster(cluster_2)){
                if(cluster_2 != cluster){
                    point_2 = cluster_first_point(cluster_2);
                    do{
                        b_tmp += d_pointPoint(point_2, point);
                    }while(point_2 = next_point(point_2));
                    b_tmp /= cluster_nb_points(cluster_2);
                    b[j] = max(b[j], b_tmp);
                }
            }
            s[j] = (b[j] - a[j]) / max(a[j], b[j]);
            j++;
        }while(point = next_point(point));
        i++;
    }while(cluster = next_cluster(cluster));

    homogeneity = 0;
    for(i = 0; i < nb_cluster; i++) homogeneity += tightness[i];
    homogeneity /= nb_cluster;

    separation = 0;
    for(i = 0; i < nb_cluster; i++){
        for(j = i+1; j < nb_cluster; j++)
            separation += d_floatFloat(balance[i], balance[j]);
    }
    separation *= 1/(float)(nb_cluster*(nb_cluster-1));

    score_DB = 0;
    for(i = 0; i < nb_cluster; i++){
        for(j = i+1; j < nb_cluster; j++){
            score_DB = max(score_DB, (tightness[i] + tightness[j])/d_floatFloat(balance[i], balance[j]));
        }
    }

    // redirection vers un fichier txt
    int saved = redirection(path, "txt");
    printf("Global measures");
    printf("\nNumber of dimensions: %d", cloud_dim(cloud));
    printf("\n\nEstimated number of clusters: %d", nb_cluster);
    printf("\nNumber of points: %d", nb_points(cloud));
    printf("\nEstimated number of noise points: %d", cluster_nb_points(cloud_first_cluster(cloud)));
    printf("\nGlobal homogeneity: %.3f", homogeneity);
    printf("\nGlobal separation: %.3f", separation);
    printf("\nDavies–Bouldin score: %.3f", score_DB);

    printf("\n\n\nDetailed measures");
    cluster = cloud_first_cluster(cloud);
    if(is_noise(cloud)) cluster = next_cluster(cluster);
    i = 0;
    j = 0;
    do{
        printf("\n\nCluster %d (in %s)", i+1, color[i % max_c + 1]);
        printf("\nNumber of points: %d", cluster_nb_points(cluster));
        printf("\nBalance point: (");
        for(j = 0; j < DIM-2; j++){
            printf("%.3f,", balance[i][j]);
        }
        printf("%.3f)", balance[i][DIM-2]);
        printf("\nHomogeneity: %.3f", tightness[i]);
        printf("\nPoint details:");
        point = cluster_first_point(cluster);
        do{
            printf("\n\t(");
            for(j = 0; j < DIM-2; j++){
                printf("%.3f,", point_coord(point, j));
            }
            printf("%.3f)", point_coord(point, DIM-2));
            printf("\n\t\tanswer: %s", point_answer(point));
            printf("\t\ta(x)=%.3f", a[j]);
            printf("\n\t\tb(x)=%.3f", b[j]);
            printf("\n\t\ts(x)=%.3f", s[j]);
            j++;
        }while(point = next_point(point));
        i++;
    }while(cluster = next_cluster(cluster));
    restauration(saved);
}
