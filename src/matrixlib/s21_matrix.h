#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
  double max_value;
} matrix_t;

enum { OK, INVALID_MATRIX, CALCULATION_ERROR, CALLOC_ERROR };

#define EPS 1e-6
#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// utill
int s21_create_minor_matrix(matrix_t *A, int size, int row, int column,
                            matrix_t *B);
void s21_create_complements_matrix(matrix_t *A, matrix_t *result);
double s21_get_determinant(matrix_t *matrix, int size);
int s21_not_valid(matrix_t *A);

#endif  //  SRC_S21_MATRIX_H_
