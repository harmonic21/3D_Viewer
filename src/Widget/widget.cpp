#include "widget.h"

#include <QOpenGLBuffer>

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QOpenGLWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::initializeGL() {
  s21_initStruct(&data);
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  colorBack = QColor(Qt::black);
  colorLine = QColor(Qt::green);
  colorPoint = QColor(Qt::darkGreen);
}

void Widget::resizeGL(int w, int h) {
  glLoadIdentity();
  glViewport(0, 0, w, h);
}

void Widget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(colorBack.redF(), colorBack.greenF(), colorBack.blueF(), 0);

  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, colorBack);
  setAutoFillBackground(true);
  setPalette(pal);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  change_projection();
  plotting();
}

void Widget::plotting() {
  float* new_arr = s21_rewrite_matrix(&data);
  glGenBuffers(1, &mVao);
  glBindBuffer(GL_ARRAY_BUFFER, mVao);
  glBufferData(GL_ARRAY_BUFFER, data.count_of_vertexes * 3 * sizeof(float),
               new_arr, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, mVao);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 3 * sizeof(float), 0);

  if (pointType != EMPTY) {
    set_Point();
  }

  if (lineType != EMPTY) {
    set_Line();
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  if (new_arr) {
    free(new_arr);
  }
  glDeleteBuffers(1, &mVao);
}

void Widget::set_Point() {
  if (pointType == POINT_ROUND) {
    glEnable(GL_POINT_SMOOTH);
  } else if (pointType == POINT_QUADRO) {
    glDisable(GL_POINT_SMOOTH);
  }
  if (pointType != EMPTY) {
    glPointSize(pointWidth);
    glColor3f(colorPoint.redF(), colorPoint.greenF(), colorPoint.blueF());
    glDrawArrays(GL_POINTS, 0, data.count_of_vertexes);
  }
}

void Widget::set_Line() {
  if (lineType == LINE_DASHED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00FF);
  }
  if (lineType != EMPTY) {
    glLineWidth(lineWidth);
    for (unsigned int i = 0; i < data.count_of_facets; i++) {
      glColor3d(colorLine.redF(), colorLine.greenF(), colorLine.blueF());
      glDrawElements(GL_LINE_LOOP,
                     data.polygons[i].numbers_of_vertexes_in_facets,
                     GL_UNSIGNED_INT, data.polygons[i].vertexes);
    }
  }
  glDisable(GL_LINE_STIPPLE);
}

void Widget::openFile() { update(); }

void Widget::rotateX(float x) {
  float result = 0.05 / M_PI * (x - xAngle);
  s21_rotation_by_ox(&data, result);
  xAngle = x;
  update();
}

void Widget::rotateY(float y) {
  float result = 0.05 / M_PI * (y - yAngle);
  s21_rotation_by_oy(&data, result);
  yAngle = y;
  update();
}

void Widget::rotateZ(float z) {
  s21_rotation_by_oz(&data, zAngle - (double)z);
  update();
  zAngle = z;
}

void Widget::mulScaleChange(float value) {
  s21_scale_mul(&data, value);
  update();
}

void Widget::delScaleChange(float value) {
  s21_scale_del(&data, value);
  update();
}

void Widget::addMoveChangeX(float value) {
  s21_move_x(&data, value);
  update();
}

void Widget::addMoveChangeY(float value) {
  s21_move_y(&data, value);
  update();
}

void Widget::addMoveChangeZ(float value) {
  s21_move_z(&data, value);
  update();
}

void Widget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void Widget::mouseMoveEvent(QMouseEvent* mo) {
  xRot += 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot += 1 / M_PI * (mo->pos().x() - mPos.x());
  mPos = mo->pos();
  update();
}

void Widget::change_projection() {
  if (projection_type == 0) {
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }
}
