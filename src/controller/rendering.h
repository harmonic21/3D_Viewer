#ifndef SRC_RENDER_H_
#define SRC_RENDER_H_

#include "../parser/s21_parser.h"

void s21_move_x(t_data* data, double a);
void s21_move_y(t_data* data, double a);
void s21_move_z(t_data* data, double a);

void s21_rotation_by_ox(t_data* data, double angle);
void s21_rotation_by_oy(t_data* data, double angle);
void s21_rotation_by_oz(t_data* data, double angle);

void s21_scale_mul(t_data* data, double a);
void s21_scale_del(t_data* data, double a);

#endif  // SRC_RENDER_H_
