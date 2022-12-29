#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMovie>
#include <QSettings>
#include <QTimer>

#include "../QtGifImage-master/src/gifimage/qgifimage.h"
#include "../Widget/widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  float scale_reduction = 0;
  float scale_increase = 0;
  float move_x_sum = 0;
  float move_y_sum = 0;
  float move_z_sum = 0;
  float move_x_sub = 0;
  float move_y_sub = 0;
  float move_z_sub = 0;
  float count = 0;
  QString file_name = "";
  QTimer *timer;
  QVector<QImage> gif;
  void set_info(QString path);

 public slots:
  void open_file();
  void press_rotate_X();
  void press_rotate_Y();
  void press_rotate_Z();
  void press_scale_higher();
  void press_scale_lower();
  void press_move_x();
  void press_move_y();
  void press_move_z();
  void press_move_x_sub();
  void press_move_y_sub();
  void press_move_z_sub();

  void set_dash_line();
  void set_solid_line();
  void set_empty_line();
  void set_thick_line();

  void set_orb_point();
  void set_empty_point();
  void set_square_point();
  void set_thick_point();
  void set_projection();

  void set_color();
  void create_screen();
  void create_gif();
  void timer_run();
  void make_gif();

  void save_setting();
  void apply_setting();
};

#endif  // MAINWINDOW_H
