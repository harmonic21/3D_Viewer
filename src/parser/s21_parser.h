#ifndef SRC_PARSER_PARSER_H
#define SRC_PARSER_PARSER_H

#include <stdlib.h>
#include <string.h>

#include "../matrixlib/s21_matrix.h"

typedef struct facets {
  unsigned int *vertexes;
  unsigned int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct s_data {
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} t_data;

int s21_readFile(const char *filename, t_data *data);
float *s21_rewrite_matrix(t_data *data);
void s21_initStruct(t_data *data);
void s21_print_all(t_data *data);
void s21_free_mem(t_data *data);

#endif  // SRC_PARSER_PARSER_H