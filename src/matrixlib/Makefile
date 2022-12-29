CC=gcc
FLAGS=-g -Wall -Wextra -Werror -std=c11 -pedantic
CFLAGS=-c $(FLAGS)
TEST_FLAGS=-lcheck -lgcov


SRC_MATRIX=s21_matrix.c
#OBJECTS
OBJ=$(notdir $(SRC_MATRIX:.c=.o))

#DIRECTORY
OBJ_DIR=objects

#INCLUDES
INCLUDE=s21_matrix.h 

vpath %.o $(OBJ_DIR)

.PHONY: all clean test gcov_report

all: s21_matrix.a

%.o: %.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(addprefix $(OBJ_DIR)/, $@) -c $<

s21_matrix.a: $(INCLUDE) $(OBJ)
	ar rcs $@  $(addprefix $(OBJ_DIR)/, $(OBJ))
	ranlib $@

clean:
	rm -rf $(OBJ_DIR)
