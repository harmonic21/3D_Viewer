CC=gcc
FLAGS=-Wall -Wextra -Werror -g
CFLAGS=-c $(FLAGS)
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	TEST_FLAGS=-lcheck -lgcov -lm -lrt -lpthread -lsubunit
else
	TEST_FLAGS=-lcheck -lgcov -lm -lpthread
endif

#SRC
SRC_CFILES=s21_parser.c rendering.c
SRC_TEST=test.c

SOURCES=./Widget/main.cpp \
		./Widget/mainwindow.cpp \
		./Widget/choosecolor.cpp \
		./Widget/glew.c \
		./Widget/widget.cpp \
		./parser/s21_parser.c \
		./controller/rendering.c

HEADERS=./Widget/mainwindow.h \
		./Widget/mwidget.h \
		./Widget/glew.h \
		./Widget/glxew.h \
		./matrixlib/s21_matrix.h \
		./parser/s21_parser.h \
		./controller/rendering.h

#OBJECTS
OBJ=$(notdir $(SRC_CFILES:.c=.o))
OBJ_TEST=$(notdir $(SRC_TEST:.c=.o))

#DIRECTORY
OBJ_DIR=./objects
SRC_DIR=./parser \
		./controller
LIB_DIR=./matrixlib
TEST_DIR=test
BD=./build/

#INCLUDES
INCLUDE=s21_parser.h \
		rendering.h \

vpath %.c $(SRC_DIR) $(TEST_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(SRC_DIR) $(LIB_DIR)
vpath %.a $(LIB_DIR)

.PHONY: all clean test gcov_report build install uninstal dvi

all: install

build: $(BD)/Widget.pro
	cd $(BD); qmake Widget.pro
	make -C $(BD)

$(BD)/Widget.pro:
	@mkdir -p ./build/ 2>/dev/null
	cp ./Widget/Widget.pro $(BD)

$(BD)%.o: */*/%.cpp
	g++ -C $< -o $@

install: build
	@mkdir -p ./Applications/ 2>/dev/null
ifeq ($(UNAME), Linux)
	cp -rf $(BD)/Widget ./Applications/
else
	cp -rf $(BD)/Widget.app ./Applications/
endif
	make clean

uninstall:
	rm -rf ./Applications/

dvi:
	latex ./Documentation/3DViewer.tex
	mv ./3DViewer.dvi ./Documentation
	rm -rf ./3DViewer.aux ./3DViewer.log
dist: install
	tar -cvf 3DViewer.tar Documentation/3DViewer.dvi 
	Applications/Widget.app
	gzip 3DViewer.tar
clang:
	bash style.sh
	

valgrind: tests
	valgrind --leak-check=full ./s21_test

%.o: %.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) -c $<

matrix.a:
	cd matrixlib && $(MAKE) s21_matrix.a && $(MAKE) clean

tests: matrix.a $(OBJ_TEST) $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR)/, $(OBJ) $(OBJ_TEST)) $(TEST_FLAGS) -o s21_test -L. $(LIB_DIR)/s21_matrix.a
	./s21_test

gcov_report:CFLAGS += -coverage
gcov_report: clean tests
	./s21_test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open ./report/index.html

clean:
	rm -rf $(OBJ_DIR) s21_test report *.info $(LIB_DIR)/s21_matrix.a ./build/*.o

fclean: clean uninstall 
	rm -rf ./build 

installtex:
	brew install --cask mactex
