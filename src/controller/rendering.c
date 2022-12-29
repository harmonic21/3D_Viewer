#include "rendering.h"

/*----------------------------------
Перемещать модель на заданное расстояние относительно осей X, Y, Z
------------------------------------*/
void s21_move_x(t_data* data, double a) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] += a;
  }
}

void s21_move_y(t_data* data, double a) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][1] += a;
  }
}

void s21_move_z(t_data* data, double a) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][2] += a;
  }
}

/*----------------------------------
Поворачивать модель на заданный угол относительно осей X, Y, Z
------------------------------------*/
void s21_rotation_by_ox(t_data* data, double angle) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    double buff_y = data->matrix_3d.matrix[i][1];
    double buff_z = data->matrix_3d.matrix[i][2];
    data->matrix_3d.matrix[i][1] = cos(angle) * buff_y + sin(angle) * buff_z;
    data->matrix_3d.matrix[i][2] = -sin(angle) * buff_y + cos(angle) * buff_z;
  }
}

void s21_rotation_by_oy(t_data* data, double angle) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    double buff_x = data->matrix_3d.matrix[i][0];
    double buff_z = data->matrix_3d.matrix[i][2];
    data->matrix_3d.matrix[i][0] = cos(angle) * buff_x + sin(angle) * buff_z;
    data->matrix_3d.matrix[i][2] = -sin(angle) * buff_x + cos(angle) * buff_z;
  }
}

void s21_rotation_by_oz(t_data* data, double angle) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    double buff_x = data->matrix_3d.matrix[i][0];
    double buff_y = data->matrix_3d.matrix[i][1];
    data->matrix_3d.matrix[i][0] = cos(angle) * buff_x - sin(angle) * buff_y;
    data->matrix_3d.matrix[i][1] = sin(angle) * buff_x + cos(angle) * buff_y;
  }
}

/*----------------------------------
Масштабировать модель на заданное значение.
------------------------------------*/
void s21_scale_mul(t_data* data, double a) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] *= a;
    data->matrix_3d.matrix[i][1] *= a;
    data->matrix_3d.matrix[i][2] *= a;
  }
}

void s21_scale_del(t_data* data, double a) {
  for (int i = 1; i < data->matrix_3d.rows; i++) {
    data->matrix_3d.matrix[i][0] /= a;
    data->matrix_3d.matrix[i][1] /= a;
    data->matrix_3d.matrix[i][2] /= a;
  }
}
