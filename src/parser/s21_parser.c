#include "s21_parser.h"

void s21_free_mem(t_data *data) {
  s21_remove_matrix(&data->matrix_3d);

  for (unsigned int i = 0; i < data->count_of_facets; i++) {
    free(data->polygons[i].vertexes);
  }
  free(data->polygons);
}

void s21_initStruct(t_data *data) {
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
  data->matrix_3d.matrix = NULL;
  data->matrix_3d.columns = 0;
  data->matrix_3d.rows = 0;
  data->matrix_3d.max_value = 0;
  data->polygons = NULL;
}

float *s21_rewrite_matrix(t_data *data) {
  float *new_matrix = calloc(data->count_of_vertexes * 3, sizeof(float));
  unsigned int k = 0;
  if (data->matrix_3d.matrix != NULL) {
    for (int i = 1; i < data->matrix_3d.rows; i++) {
      for (int j = 0; j < data->matrix_3d.columns; j++) {
        new_matrix[k] =
            data->matrix_3d.matrix[i][j] / data->matrix_3d.max_value;
        k++;
      }
    }
  }
  return new_matrix;
}

static void s21_fillPolygons(char *result, t_data *data,
                             unsigned int *vert_iterator) {
  int i = 0;
  char *token;

  while ((token = strtok_r(result, " ", &result))) {
    if (*token == '\n' || *token == ' ') {
      break;
    }
    if (*token != '0') {
      data->polygons[*vert_iterator].vertexes[i] = atoi(token) - 1;
      i++;
    }
  }
}

static void s21_countVertexesInFacets(char *result, t_data *data,
                                      unsigned int *vert_iterator) {
  char *temp = strdup(result);
  char *for_free = temp;
  char *token;

  while ((token = strtok_r(temp, " ", &temp))) {
    if (*token != '0' && *token != '\n') {
      data->polygons[*vert_iterator].numbers_of_vertexes_in_facets++;
    }
  }
  free(for_free);
}

static void s21_fillMatrixOfVertexes(char *result, t_data *data,
                                     unsigned int *iterator) {
  char *token;
  int i = 0;

  while ((token = strtok_r(result, " ", &result))) {
    data->matrix_3d.matrix[*iterator][i] = atof(token);
    if (data->matrix_3d.max_value <
        fabs(data->matrix_3d.matrix[*iterator][i])) {
      data->matrix_3d.max_value = fabs(data->matrix_3d.matrix[*iterator][i]);
    }
    i++;
  }
}

static int s21_parseValues(const char *filename, t_data *data) {
  int errorValue = 0;
  FILE *file;
  file = fopen(filename, "r");
  if (file != NULL) {
    char *result = NULL;
    size_t len = 0;
    unsigned int iterator = 1;
    unsigned int vert_iterator = 0;

    s21_create_matrix(data->count_of_vertexes + 1, 3, &data->matrix_3d);
    data->polygons = calloc(data->count_of_facets, sizeof(polygon_t));
    while (getline(&result, &len, file) != -1) {
      if (*result == 'v' && *(result + 1) == ' ') {
        s21_fillMatrixOfVertexes(result + 1, data, &iterator);
        iterator++;
      } else if (*result == 'f' && *(result + 1) == ' ') {
        s21_countVertexesInFacets(result + 1, data, &vert_iterator);
        data->polygons[vert_iterator].vertexes =
            calloc(data->polygons[vert_iterator].numbers_of_vertexes_in_facets,
                   sizeof(unsigned int));
        s21_fillPolygons(result + 1, data, &vert_iterator);
        vert_iterator++;
      }
    }
    fclose(file);
    free(result);
  } else {
    errorValue = 1;
  }
  return errorValue;
}

static int s21_parseCount(const char *filename, t_data *data) {
  int errorValue = 0;
  FILE *file;

  file = fopen(filename, "r");
  if (file != NULL) {
    char *result = NULL;
    size_t len = 0;
    s21_initStruct(data);

    while (getline(&result, &len, file) != -1) {
      if (*result == 'v' && *(result + 1) == ' ') {
        data->count_of_vertexes++;
      } else if (*result == 'f' && *(result + 1) == ' ') {
        data->count_of_facets++;
      }
    }
    fclose(file);
    free(result);
  } else {
    errorValue = 1;
  }
  return errorValue;
}

int s21_readFile(const char *filename, t_data *data) {
  int errorValue = 0;
  errorValue = s21_parseCount(filename, data);
  if (!errorValue) {
    errorValue = s21_parseValues(filename, data);
  }
  return errorValue;
}
