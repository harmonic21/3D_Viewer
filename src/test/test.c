#include <check.h>
#include <math.h>

#include "../controller/rendering.h"
#include "../parser/s21_parser.h"

START_TEST(s21_read_file) {
  t_data data;
  matrix_t m;
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0, 0, 0};
  double mat1[] = {-1.0, -1.0, -1.0};
  double mat2[] = {-1.0, -1.0, 1.0};
  double mat3[] = {-1.0, 1.0, -1.0};
  double mat4[] = {-1.0, 1.0, 1.0};
  double mat5[] = {1.0, -1.0, -1.0};
  double mat6[] = {1.0, -1.0, 1.0};
  double mat7[] = {1.0, 1.0, -1.0};
  double mat8[] = {1.0, 1.0, 1.0};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;
  int result_read = s21_readFile("./obj/cube.obj", &data);
  ck_assert_int_eq(result_read, 0);
  ck_assert_uint_eq(data.count_of_facets, 10);
  ck_assert_uint_eq(data.count_of_vertexes, 8);
  int result_eq_matrix = s21_eq_matrix(&m, &data.matrix_3d);
  ck_assert_int_eq(result_eq_matrix, 1);
  s21_free_mem(&data);
  free(m.matrix);
}
END_TEST

START_TEST(s21_read_big_file) {
  t_data data;
  char *path = "./obj/cat.obj";
  int result = s21_readFile(path, &data);
  ck_assert_int_eq(result, 0);
  ck_assert_uint_eq(data.count_of_facets, 2082);
  ck_assert_uint_eq(data.count_of_vertexes, 1136);
  s21_free_mem(&data);
}

START_TEST(s21_wrong_path) {
  t_data data;
  char *path = "../test.obj";
  int result = s21_readFile(path, &data);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(s21_rewrite) {
  t_data data;
  char *path = "./obj/cube.obj";
  int result = s21_readFile(path, &data);
  float *new_matrix = s21_rewrite_matrix(&data);
  int k = 0;
  for (int i = 1; i < data.matrix_3d.rows; i++) {
    for (int j = 0; j < data.matrix_3d.columns; j++) {
      ck_assert_double_eq_tol(data.matrix_3d.matrix[i][j], new_matrix[k], 1e-6);
      k++;
    }
  }
  ck_assert_int_eq(result, 0);
  free(new_matrix);
  s21_free_mem(&data);
}
END_TEST

START_TEST(s21_shift_x) {
  t_data data;
  t_data data_1;
  char *path = "./obj/cube.obj";
  s21_readFile(path, &data);
  s21_readFile(path, &data_1);
  double buf = 2.5;
  s21_move_x(&data, buf);
  for (int i = 1; i < data_1.matrix_3d.rows; i++) {
    data_1.matrix_3d.matrix[i][0] += buf;
  }
  int error = s21_eq_matrix(&data_1.matrix_3d, &data.matrix_3d);
  ck_assert_int_eq(1, error);
  s21_free_mem(&data);
  s21_free_mem(&data_1);
}
END_TEST

START_TEST(s21_shift_y) {
  t_data data;
  t_data data_1;
  char *path = "./obj/cube.obj";
  s21_readFile(path, &data);
  s21_readFile(path, &data_1);
  double buf = 2.5;
  s21_move_y(&data, buf);
  for (int i = 1; i < data_1.matrix_3d.rows; i++) {
    data_1.matrix_3d.matrix[i][1] += buf;
  }
  int error = s21_eq_matrix(&data_1.matrix_3d, &data.matrix_3d);
  s21_free_mem(&data);
  s21_free_mem(&data_1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(s21_shift_z) {
  t_data data;
  t_data data_1;
  char *path = "./obj/cube.obj";
  s21_readFile(path, &data);
  s21_readFile(path, &data_1);
  double buf = 2.5;
  s21_move_z(&data, buf);
  for (int i = 1; i < data_1.matrix_3d.rows; i++) {
    data_1.matrix_3d.matrix[i][2] += buf;
  }
  int error = s21_eq_matrix(&data_1.matrix_3d, &data.matrix_3d);
  s21_free_mem(&data);
  s21_free_mem(&data_1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(s21_rotationX) {
  t_data data;
  matrix_t m;
  char *path = "./obj/cube.obj";
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0.000, 0.000, 0.000};
  double mat1[] = {-1.0, 0.675262, -1.242586};
  double mat2[] = {-1.0, -1.242586, -0.675262};
  double mat3[] = {-1.0, 1.242586, 0.675262};
  double mat4[] = {-1.0, -0.675262, 1.242586};
  double mat5[] = {1.000000, 0.675262, -1.242586};
  double mat6[] = {1.000000, -1.242586, -0.675262};
  double mat7[] = {1.000000, 1.242586, 0.675262};
  double mat8[] = {1.000000, -0.675262, 1.242586};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;

  int result = s21_readFile(path, &data);
  s21_rotation_by_ox(&data, 5);
  int error = s21_eq_matrix(&data.matrix_3d, &m);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, error);
  s21_free_mem(&data);
  free(m.matrix);
}
END_TEST

START_TEST(s21_rotationY) {
  t_data data;
  matrix_t m;
  char *path = "./obj/cube.obj";
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0.000000, 0.000000, 0.000000};
  double mat1[] = {0.675262, -1.000000, -1.242586};
  double mat2[] = {-1.242586, -1.000000, -0.675262};
  double mat3[] = {0.675262, 1.000000, -1.242586};
  double mat4[] = {-1.242586, 1.000000, -0.675262};
  double mat5[] = {1.242586, -1.000000, 0.675262};
  double mat6[] = {-0.675262, -1.000000, 1.242586};
  double mat7[] = {1.242586, 1.000000, 0.675262};
  double mat8[] = {-0.675262, 1.000000, 1.242586};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;

  int result = s21_readFile(path, &data);
  s21_rotation_by_oy(&data, 5);

  int error = s21_eq_matrix(&data.matrix_3d, &m);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, error);
  s21_free_mem(&data);
  free(m.matrix);
}
END_TEST

START_TEST(s21_rotationZ) {
  t_data data;
  matrix_t m;
  char *path = "./obj/cube.obj";
  m.matrix = calloc(9, sizeof(double **));
  double mat0[] = {0.000000, 0.000000, 0.000000};
  double mat1[] = {-1.242586, 0.675262, -1.000000};
  double mat2[] = {-1.242586, 0.675262, 1.000000};
  double mat3[] = {0.675262, 1.242586, -1.000000};
  double mat4[] = {0.675262, 1.242586, 1.000000};
  double mat5[] = {-0.675262, -1.242586, -1.000000};
  double mat6[] = {-0.675262, -1.242586, 1.000000};
  double mat7[] = {1.242586, -0.675262, -1.000000};
  double mat8[] = {1.242586, -0.675262, 1.000000};
  m.matrix[0] = &mat0[0];
  m.matrix[1] = &mat1[0];
  m.matrix[2] = &mat2[0];
  m.matrix[3] = &mat3[0];
  m.matrix[4] = &mat4[0];
  m.matrix[5] = &mat5[0];
  m.matrix[6] = &mat6[0];
  m.matrix[7] = &mat7[0];
  m.matrix[8] = &mat8[0];
  m.rows = 9;
  m.columns = 3;

  int result = s21_readFile(path, &data);
  s21_rotation_by_oz(&data, 5);

  int not_error = s21_eq_matrix(&data.matrix_3d, &m);
  ck_assert_int_eq(0, result);
  ck_assert_int_eq(1, not_error);
  s21_free_mem(&data);
  free(m.matrix);
}
END_TEST

START_TEST(s21_scale_bigger) {
  t_data data;
  t_data data_1;
  char *path = "./obj/cube.obj";
  s21_readFile(path, &data);
  s21_readFile(path, &data_1);
  double buf = 2.5;
  s21_scale_mul(&data, buf);
  for (int i = 1; i < data_1.matrix_3d.rows; i++) {
    data_1.matrix_3d.matrix[i][0] *= buf;
    data_1.matrix_3d.matrix[i][1] *= buf;
    data_1.matrix_3d.matrix[i][2] *= buf;
  }
  int error = s21_eq_matrix(&data_1.matrix_3d, &data.matrix_3d);
  s21_free_mem(&data);
  s21_free_mem(&data_1);
  ck_assert_int_eq(1, error);
}
END_TEST

START_TEST(s21_scale_smaller) {
  t_data data;
  t_data data_1;
  char *path = "./obj/cube.obj";
  s21_readFile(path, &data);
  s21_readFile(path, &data_1);
  double buf = 5;
  s21_scale_del(&data, buf);
  for (int i = 1; i < data_1.matrix_3d.rows; i++) {
    data_1.matrix_3d.matrix[i][0] /= buf;
    data_1.matrix_3d.matrix[i][1] /= buf;
    data_1.matrix_3d.matrix[i][2] /= buf;
  }
  int error = s21_eq_matrix(&data_1.matrix_3d, &data.matrix_3d);
  s21_free_mem(&data);
  s21_free_mem(&data_1);
  ck_assert_int_eq(1, error);
}
END_TEST

Suite *s21_viewer_suite() {
  Suite *s;

  TCase *tc_parser, *tc_render;
  s = suite_create("s21_viewer");

  tc_parser = tcase_create("pars");
  tcase_add_test(tc_parser, s21_read_file);
  tcase_add_test(tc_parser, s21_read_big_file);
  tcase_add_test(tc_parser, s21_wrong_path);
  tcase_add_test(tc_parser, s21_rewrite);
  suite_add_tcase(s, tc_parser);

  tc_render = tcase_create("render");
  tcase_add_test(tc_render, s21_shift_x);
  tcase_add_test(tc_render, s21_shift_z);
  tcase_add_test(tc_render, s21_shift_y);
  tcase_add_test(tc_render, s21_scale_bigger);
  tcase_add_test(tc_render, s21_scale_smaller);
  tcase_add_test(tc_render, s21_rotationX);
  tcase_add_test(tc_render, s21_rotationY);
  tcase_add_test(tc_render, s21_rotationZ);
  suite_add_tcase(s, tc_render);

  return s;
}

int main() {
  int no_failed = 0;
  Suite *s;
  SRunner *runner;

  s = s21_viewer_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
