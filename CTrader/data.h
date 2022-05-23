#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N;
double **data;
void collect_data(char* file_name);
void read_csv(int row, int col, char *filename, double **data);
#endif