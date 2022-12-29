#ifndef WIDGET_H
#define WIDGET_H

#define GLEW_STATIC
#include "glew.h"

#include <QMouseEvent>
#include <QOpenGLWidget>

#define GL_SILENCE_DEPRECATION

extern "C" {
#include "../controller/rendering.h"
#include "../parser/s21_parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QOpenGLWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  t_data data;

  void openFile();
  void rotateX(float x);
  void rotateY(float y);
  void rotateZ(float z);
  void mulScaleChange(float value);
  void delScaleChange(float value);
  void addMoveChangeX(float value);
  void addMoveChangeY(float value);
  void addMoveChangeZ(float value);
  void change_projection();

  void getVertexArray();
  void getColorArray();

  void set_Line();
  void set_Point();

  QColor colorBack;
  QColor colorLine;
  QColor colorPoint;

  int lineType = 1;
  float lineWidth = 1;

  int pointType = 1;
  float pointWidth = 1;
  float *new_arr;

  int projection_type = 0;  // 0 - parallel, 1 - central

  enum {
    EMPTY = 0,
    POINT_ROUND = 1,
    POINT_QUADRO = 2,
    LINE_SOLID = 1,
    LINE_DASHED = 2,
    IS_CHECKED = 1
  };

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  Ui::Widget *ui;
  GLuint mVao;
  float xRot = 0;
  float yRot = 0;
  float zRot = 0;
  float xAngle = 0;
  float yAngle = 0;
  float zAngle = 0;
  GLfloat colorArray[3][3];
  QPoint mPos;
  std::vector<GLuint> mBuffers;

  void mousePressEvent(QMouseEvent *mo) override;
  void mouseMoveEvent(QMouseEvent *mo) override;
  void plotting();
};
#endif  // WIDGET_H
