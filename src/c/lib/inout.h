#ifndef INOUT_H_
#define INOUT_H_

#include "cloud.h"
#include "cluster.h"
#include "point.h"

#define MAX_LINE 128
#define SCALE 100
#define PRINT_RADIUS 1
#define max(a,b) (((a)>(b))?(a):(b))


cloud_t* read_data(char* path);

void make_stats(char* path, cloud_t* cloud);
void write_output(char* path, cloud_t* cloud);
char* extract_filename(char* path, char* algo);

#endif