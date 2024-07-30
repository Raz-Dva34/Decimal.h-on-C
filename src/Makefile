CC = gcc
FLAGCOMP = -Wall -Werror -Wextra -std=c11
FLAG_O = -o
FLAG_C = -c
FLAG_T = -t
FLAG_D = -d
WAY_FUN = ./functions/*/
WAY_ADD = ./functions/
WAY_TEST = ./s21_tests/
OS := $(shell uname)

ifeq ($(OS),Linux)
FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
OPENF = xdg-open
else
FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
OPENF = open
endif

all: clean s21_decimal.a test gcov_report
	@mkdir spare_files
	@mv *.o *.a *.info spare_files
	-rm -rf ./spare_files/*.o

test: clean s21_decimal.a
	$(CC) $(FLAGCOMP) s21_tests.c $(WAY_TEST)*.c $(WAY_FUN)*.c $(WAY_ADD)*.c s21_decimal.a $(FLAGS) $(FLAG_O) unit_test
	./unit_test

s21_decimal.a:
	$(CC) $(FLAGCOMP) $(FLAG_C) $(WAY_FUN)s21_*.c $(WAY_ADD)*.c
	ar -crs s21_decimal.a s21_*.o
	ranlib s21_decimal.a

gcov_report: clean test
	lcov $(FLAG_T) "./unit_test"  $(FLAG_O) report.info --no-external $(FLAG_C) $(FLAG_D) .
	genhtml $(FLAG_O) report report.info
	$(OPENF) ./report/index.html
	-rm -rf *.gcno *gcda *.gco

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt *.gch unit_test
	-rm -rf tests
	-rm -rf report
	-rm -rf spare_files
	-rm -rf .clang-format
	find . -type d -name 'tests.dSYM' -exec rm -r {} +

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.c *.h ./*/*.c ./*/*/*.c

rebuild: clean all
