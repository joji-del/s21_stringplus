GCC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(wildcard s21_*.c)
HEADER = $(wildcard s21_*.h)
OBJECTS = $(patsubst %.c, %.o, ${SOURCE})
TESTS_SOURCE = tests.c
TESTS_OBJECTS = $(patsubst %.c, %.o, ${TESTS_SOURCE})
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    OPEN_CMD = xdg-open
    ADD_LIB = -pthread -lcheck_pic -lrt -lm -lsubunit
    BREW = .
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lcheck -lm -lpthread
	BREW := ${HOME}/homebrew
endif

PATH := $(BREW)/bin:$(PATH)

all: s21_string.a

s21_string.a: ${SOURCE}
	$(GCC) $(CFLAGS) ${SOURCE}
	ar rc $@ $(OBJECTS)
	ranlib $@

test: ${TESTS_SOURCE} s21_string.a
	@echo ${ADD_LIB}
	${GCC} $(LDFLAGS) -o test ${TESTS_SOURCE} s21_string.a ${ADD_LIB}
	./test

gcov_report: clean lcov ${SOURCE}
	${GCC} --coverage -fprofile-arcs -ftest-coverage ${SOURCE} ${TESTS_SOURCE} -o s21_test ${ADD_LIB}
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report
	-rm -rf s21_test

.PHONY: all clean check lcov