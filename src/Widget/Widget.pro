QT       += core gui opengl
!linux {
	QT += widgets openglwidgets
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=../Widget/

SOURCES += \
    ../controller/rendering.c \
    ../matrixlib/s21_matrix.c \
    ../parser/s21_parser.c \
    ../Widget/glew.c \
    ../Widget/main.cpp \
    ../Widget/mainwindow.cpp \
    ../Widget/widget.cpp

HEADERS += \
    ../controller/rendering.h \
    ../matrixlib/s21_matrix.h \
    ../parser/s21_parser.h \
    ../Widget/glew.h \
    ../Widget/glxew.h \
    ../Widget/mainwindow.h \
    ../Widget/widget.h

include (../QtGifImage-master/src/gifimage/qtgifimage.pri)

FORMS += \
    ../Widget/mainwindow.ui \
    ../Widget/widget.ui

TRANSLATIONS += \
    ../Widget/Widget_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../QtGifImage-master/qtgifimage.pro

