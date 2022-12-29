#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows <= 0 || columns <= 0) {
    return INVALID_MATRIX;
  }
  result->rows = rows;
  result->columns = columns;
  result->max_value = 0;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (!result->matrix) {
    return CALLOC_ERROR;
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (!result->matrix[i]) {
      s21_remove_matrix(result);
      return CALLOC_ERROR;
    }
  }
  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (s21_not_valid(A) || s21_not_valid(B)) {
    return FAILURE;
  }
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      int flag = 0;
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        break;
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}

/**
 * Вычисление методом матрицы алгебраических дополнений
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }
  double det = 0.0;
  s21_determinant(A, &det);
  if (fabs(det) < EPS) {
    return CALCULATION_ERROR;
  }
  matrix_t complements = {0};
  matrix_t invers = {0};

  int size = A->rows;
  s21_create_matrix(size, size, result);

  s21_calc_complements(A, &complements);
  s21_transpose(&complements, &invers);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result->matrix[i][j] = invers.matrix[i][j] / det;
    }
  }
  s21_remove_matrix(&invers);
  s21_remove_matrix(&complements);
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_not_valid(A) || s21_not_valid(B)) {
    return INVALID_MATRIX;
  }
  if (A->columns != B->rows) {
    return CALCULATION_ERROR;
  }
  int res = OK;
  res = s21_create_matrix(A->rows, B->columns, result);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  res = s21_create_matrix(A->rows, A->columns, result);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_not_valid(A) || s21_not_valid(B)) {
    return INVALID_MATRIX;
  }
  res = s21_create_matrix(A->rows, A->columns, result);
  if ((A->rows == B->rows) && (A->columns == B->columns) && !res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_not_valid(A) || s21_not_valid(B)) {
    return INVALID_MATRIX;
  }
  res = s21_create_matrix(A->rows, A->columns, result);
  if ((A->rows == B->rows) && (A->columns == B->columns) && !res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  int res = s21_create_matrix(A->columns, A->rows, result);
  if (!res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
    A = NULL;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  if (A->columns != A->rows) {
    return CALCULATION_ERROR;
  }
  *result = s21_get_determinant(A, A->rows);
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  if (A->columns != A->rows) {
    return CALCULATION_ERROR;
  }
  res = s21_create_matrix(A->rows, A->columns, result);
  if (!res) {
    s21_create_complements_matrix(A, result);
  }
  return res;
}

int s21_not_valid(matrix_t *A) {
  return A == NULL || A->matrix == NULL || A->columns <= 0 || A->rows <= 0;
}

int s21_create_minor_matrix(matrix_t *A, int size, int row, int column,
                            matrix_t *B) {
  int res = OK;
  int offset_row = 0;
  int offset_column = 0;
  res = s21_create_matrix(size - 1, size - 1, B);
  if (!res) {
    for (int i = 0; i < size - 1; i++) {
      if (i == row) {
        offset_row = 1;
      }
      offset_column = 0;
      for (int j = 0; j < size - 1; j++) {
        if (j == column) {
          offset_column = 1;
        }
        B->matrix[i][j] = A->matrix[i + offset_row][j + offset_column];
      }
    }
  }
  return res;
}

void s21_create_complements_matrix(matrix_t *A, matrix_t *result) {
  int size = A->rows;
  matrix_t new_matrix = {0};
  int degree = 1;
  if (size == 1) {
    result->matrix[0][0] = 1;
  } else {
    for (int i = 0; i < size; i++) {
      degree = i % 2 ? -1 : 1;
      for (int j = 0; j < size; j++) {
        s21_create_minor_matrix(A, size, i, j, &new_matrix);
        double temp = s21_get_determinant(&new_matrix, size - 1);
        result->matrix[i][j] = degree * temp;
        degree *= (-1);
        s21_remove_matrix(&new_matrix);
      }
    }
  }
}

double s21_get_determinant(matrix_t *matrix, int size) {
  double det = 0.0;
  int degree = 1;
  if (size == 1) {
    return matrix->matrix[0][0];
  } else if (size == 2) {
    return matrix->matrix[0][0] * matrix->matrix[1][1] -
           (matrix->matrix[0][1] * matrix->matrix[1][0]);
  } else if (size > 2) {
    matrix_t new_matrix = {0};
    for (int j = 0; j < size; j++) {
      s21_create_minor_matrix(matrix, size, 0, j, &new_matrix);
      det += degree * (matrix->matrix[0][j] *
                       s21_get_determinant(&new_matrix, size - 1));
      degree *= (-1);
      s21_remove_matrix(&new_matrix);
    }
  }
  return det;
}
