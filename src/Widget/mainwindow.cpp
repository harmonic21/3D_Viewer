#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D_Viewer");
  timer = new QTimer(0);

  connect(ui->openFile, SIGNAL(clicked()), this, SLOT(open_file()));
  connect(ui->OX, SIGNAL(valueChanged(int)), this, SLOT(press_rotate_X()));
  connect(ui->OY, SIGNAL(valueChanged(int)), this, SLOT(press_rotate_Y()));
  connect(ui->OZ, SIGNAL(valueChanged(int)), this, SLOT(press_rotate_Z()));
  connect(ui->scale_mul, SIGNAL(valueChanged(double)), this,
          SLOT(press_scale_higher()));
  connect(ui->scale_del, SIGNAL(valueChanged(double)), this,
          SLOT(press_scale_lower()));
  connect(ui->moveX_sum, SIGNAL(valueChanged(double)), this,
          SLOT(press_move_x()));
  connect(ui->moveY_sum, SIGNAL(valueChanged(double)), this,
          SLOT(press_move_y()));
  connect(ui->moveZ_sum, SIGNAL(valueChanged(double)), this,
          SLOT(press_move_z()));
  connect(ui->moveX_sub, SIGNAL(valueChanged(double)), this,
          SLOT(press_move_x_sub()));
  connect(ui->moveY_sub, SIGNAL(valueChanged(double)), this,
          SLOT(press_move_y_sub()));
  connect(ui->moveZ_sub, SIGNAL(valueChanged(double)), this,
          SLOT(press_move_z_sub()));

  connect(ui->solid_line, SIGNAL(clicked()), this, SLOT(set_solid_line()));
  connect(ui->dash_line, SIGNAL(clicked()), this, SLOT(set_dash_line()));
  connect(ui->empty_line, SIGNAL(clicked()), this, SLOT(set_empty_line()));
  connect(ui->thick_line, SIGNAL(valueChanged(int)), this,
          SLOT(set_thick_line()));

  connect(ui->orb_point, SIGNAL(clicked()), this, SLOT(set_orb_point()));
  connect(ui->empty_point, SIGNAL(clicked()), this, SLOT(set_empty_point()));
  connect(ui->square_point, SIGNAL(clicked()), this, SLOT(set_square_point()));
  connect(ui->thick_point, SIGNAL(valueChanged(int)), this,
          SLOT(set_thick_point()));
  connect(ui->color, SIGNAL(clicked()), this, SLOT(set_color()));
  connect(ui->proj_central, SIGNAL(clicked()), this, SLOT(set_projection()));
  connect(ui->proj_parallel, SIGNAL(clicked()), this, SLOT(set_projection()));

  connect(ui->create_screen, SIGNAL(textActivated(QString)), this,
          SLOT(create_screen()));
  connect(ui->gif, SIGNAL(clicked()), this, SLOT(create_gif()));
  connect(timer, SIGNAL(timeout()), this, SLOT(timer_run()));

  connect(ui->save_setting, SIGNAL(clicked()), this, SLOT(save_setting()));
  connect(ui->apply_setting, SIGNAL(clicked()), this, SLOT(apply_setting()));
}

MainWindow::~MainWindow() {
  delete timer;
  delete ui;
}

void MainWindow::open_file() {
  s21_free_mem(&ui->widget->data);
  s21_initStruct(&ui->widget->data);
  QString file =
      QFileDialog::getOpenFileName(this, "Выберите файл", ".", tr("(*.obj)"));
  if (file != "") {
    int error_val = 0;
    QByteArray q_path = file.toLocal8Bit();
    char *result_path = q_path.data();
    error_val = s21_readFile(result_path, &ui->widget->data);
    if (!error_val) {
      ui->widget->openFile();
      set_info(file);
    } else {
      ui->file_name->setText("File not valid");
    }
  }
}

void MainWindow::set_info(QString path) {
  QString count_of_vertexes =
      QString::number(ui->widget->data.count_of_vertexes);
  QString count_of_facets = QString::number(ui->widget->data.count_of_facets);
  int index = path.lastIndexOf("/");
  int size = path.length();
  file_name = path.right(size - index - 1);
  ui->vertexes->setText(count_of_vertexes);
  ui->polygons->setText(count_of_facets);
  ui->file_name->setText(file_name);
}

void MainWindow::press_rotate_X() { ui->widget->rotateX(ui->OX->value()); }

void MainWindow::press_rotate_Y() { ui->widget->rotateY(ui->OY->value()); }

void MainWindow::press_rotate_Z() { ui->widget->rotateZ(ui->OZ->value()); }

void MainWindow::press_scale_higher() {
  float scale = ui->scale_mul->value();
  if (scale_increase != 0 && scale < scale_increase) {
    float difference = scale_increase - scale;
    ui->widget->delScaleChange(difference + scale_increase);
  } else {
    ui->widget->mulScaleChange(scale);
  }
  scale_increase = scale;
}

void MainWindow::press_scale_lower() {
  float scale = ui->scale_del->value();
  if (scale_reduction != 0 && scale < scale_reduction) {
    float difference = scale_reduction - scale;
    ui->widget->mulScaleChange(difference + scale_reduction);
  } else {
    ui->widget->delScaleChange(scale);
  }
  scale_reduction = scale;
}

void MainWindow::press_move_x() {
  float sumX = ui->moveX_sum->value();
  if (move_x_sum != 0 && sumX < move_x_sum) {
    ui->widget->addMoveChangeX(move_x_sum * (-1));
  } else {
    ui->widget->addMoveChangeX(sumX);
  }
  move_x_sum = sumX;
}

void MainWindow::press_move_y() {
  float sumY = ui->moveY_sum->value();
  if (move_y_sum != 0 && sumY < move_y_sum) {
    ui->widget->addMoveChangeY(move_y_sum * (-1));
  } else {
    ui->widget->addMoveChangeY(sumY);
  }
  move_y_sum = sumY;
}

void MainWindow::press_move_z() {
  float sumZ = ui->moveZ_sum->value();
  if (move_z_sum != 0 && sumZ < move_z_sum) {
    ui->widget->addMoveChangeZ(move_z_sum * (-1));
  } else {
    ui->widget->addMoveChangeZ(sumZ);
  }
  move_z_sum = sumZ;
}

void MainWindow::press_move_x_sub() {
  float subX = ui->moveX_sub->value();
  if (move_x_sub != 0 && subX < move_x_sub) {
    ui->widget->addMoveChangeX(move_x_sub);
  } else {
    ui->widget->addMoveChangeX(subX * (-1));
  }
  move_x_sub = subX;
}

void MainWindow::press_move_y_sub() {
  float subY = ui->moveY_sub->value();
  if (move_y_sub != 0 && subY < move_y_sub) {
    ui->widget->addMoveChangeY(move_y_sub);
  } else {
    ui->widget->addMoveChangeY(subY * (-1));
  }
  move_y_sub = subY;
}

void MainWindow::press_move_z_sub() {
  float subZ = ui->moveZ_sub->value();
  if (move_z_sub != 0 && subZ < move_z_sub) {
    ui->widget->addMoveChangeZ(move_z_sub * (-1));
  } else {
    ui->widget->addMoveChangeZ(subZ);
  }
  move_z_sub = subZ;
}

void MainWindow::set_dash_line() {
  ui->widget->lineType = ui->widget->LINE_DASHED;
  ui->widget->update();
}

void MainWindow::set_solid_line() {
  ui->widget->lineType = ui->widget->LINE_SOLID;
  ui->widget->update();
}

void MainWindow::set_empty_line() {
  ui->widget->lineType = ui->widget->EMPTY;
  ui->widget->update();
}

void MainWindow::set_thick_line() {
  ui->widget->lineWidth = ui->thick_line->value();
  ui->widget->update();
}

void MainWindow::set_orb_point() {
  ui->widget->pointType = ui->widget->POINT_ROUND;
  ui->widget->update();
}
void MainWindow::set_empty_point() {
  ui->widget->pointType = ui->widget->EMPTY;
  ui->widget->update();
}

void MainWindow::set_square_point() {
  ui->widget->pointType = ui->widget->POINT_QUADRO;
  ui->widget->update();
}

void MainWindow::set_thick_point() {
  ui->widget->pointWidth = ui->thick_point->value();
  ui->widget->update();
}

void MainWindow::set_color() {
  if (ui->color_point->isChecked()) {
    ui->widget->colorPoint = QColorDialog::getColor(Qt::gray);
  } else if (ui->color_back->isChecked()) {
    ui->widget->colorBack = QColorDialog::getColor(Qt::gray);
  } else if (ui->color_line->isChecked()) {
    ui->widget->colorLine = QColorDialog::getColor(Qt::gray);
  }
  ui->widget->update();
}

void MainWindow::create_screen() {
  QString current_type = ui->create_screen->currentText();

  QString screen =
      QFileDialog::getSaveFileName(this, "Save screen as:", "", current_type);
  if (screen != nullptr) {
    QFile file(screen);
    file.open(QIODevice::WriteOnly);
    QRect rect(0, 0, ui->widget->width(), ui->widget->height());
    QPixmap map = ui->widget->grab(rect);
    map.copy(rect).toImage().save(&file, current_type.toStdString().c_str());
  }
}

void MainWindow::create_gif() {
  timer->start(100);
  timer_run();
  count = 0.0;
}

void MainWindow::timer_run() {
  if (count <= 5.0) {
    gif.push_back(ui->widget->grab().toImage());
    count += 0.1;
  } else {
    make_gif();
    timer->stop();
  }
}

void MainWindow::make_gif() {
  QString gif_name =
      QFileDialog::getSaveFileName(this, "Save gif", "", "*.gif");
  QGifImage gif_image(QSize(640, 480));
  gif_image.setDefaultDelay(100);

  for (QVector<QImage>::Iterator screen = gif.begin(); screen != gif.end();
       ++screen) {
    gif_image.addFrame(*screen);
  }
  gif_image.save(gif_name);
  gif.clear();
  count = 0.0;
}

void MainWindow::set_projection() {
  if (ui->proj_central->isChecked()) {
    ui->widget->projection_type = 1;
  } else if (ui->proj_parallel->isChecked()) {
    ui->widget->projection_type = 0;
  }
  ui->widget->update();
}

void MainWindow::save_setting() {
  QSettings settings(QApplication::applicationDirPath() + "/user_settings",
                     QSettings::NativeFormat);
  settings.setValue("lineType", ui->widget->lineType);
  settings.setValue("lineWidth", ui->widget->lineWidth);

  settings.setValue("pointType", ui->widget->pointType);
  settings.setValue("pointWidth", ui->widget->pointWidth);

  settings.setValue("colorPoint", ui->widget->colorPoint);
  settings.setValue("colorBack", ui->widget->colorBack);
  settings.setValue("colorLine", ui->widget->colorLine);

  settings.setValue("projection_type", ui->widget->projection_type);
}

void MainWindow::apply_setting() {
  QSettings settings(QApplication::applicationDirPath() + "/user_settings",
                     QSettings::NativeFormat);

  ui->widget->lineType = settings.value("lineType").toInt();
  if (ui->widget->lineType == ui->widget->EMPTY)
    ui->empty_line->setChecked(true);
  else if (ui->widget->lineType == ui->widget->LINE_SOLID)
    ui->solid_line->setChecked(true);
  else
    ui->dash_line->setChecked(true);

  ui->widget->lineWidth = settings.value("lineWidth").toFloat();
  ui->thick_line->setValue(ui->widget->lineWidth);

  ui->widget->pointType = settings.value("pointType").toInt();
  if (ui->widget->pointType == ui->widget->EMPTY)
    ui->empty_point->setChecked(true);
  else if (ui->widget->pointType == ui->widget->POINT_ROUND)
    ui->orb_point->setChecked(true);
  else
    ui->square_point->setChecked(true);

  ui->widget->pointWidth = settings.value("pointWidth").toFloat();
  ui->thick_point->setValue(ui->widget->pointWidth);

  ui->widget->colorBack = settings.value("colorBack").value<QColor>();
  ui->widget->colorLine = settings.value("colorLine").value<QColor>();
  ui->widget->colorPoint = settings.value("colorPoint").value<QColor>();

  ui->widget->projection_type = settings.value("projection_type").toInt();
  if (ui->widget->projection_type == 1)
    ui->proj_central->setChecked(true);
  else
    ui->proj_parallel->setChecked(true);

  ui->widget->update();
}
