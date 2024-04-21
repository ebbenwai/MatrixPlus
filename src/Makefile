CC=gcc
CFLAGS=  -std=c++17 -Wall -Werror -Wextra 
CHECKFLAGS=-lgtest 
REPORTDIR=gcov_report
GCOV=--coverage
OS = $(shell uname)

ifeq ($(OS),Linux)
    det_OS = -lcheck  -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif


all: test

s21_matrix.a:
	$(CC) -c s21_matrix.cpp -o s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o

test: clean
	$(CC) $(CFLAGS) $(GCOV) -c s21_matrix.cpp -lstdc++ -lm
	$(CC) $(CFLAGS) -c tests.cpp $(CHECKFLAGS) -lstdc++ -lm
	$(CC) $(CFLAGS) $(GCOV) -o matrix tests.o s21_matrix.o $(CHECKFLAGS) -lstdc++ -lm
	./matrix

check:
	cppcheck *.cpp && cppcheck --enable=all --language=c++ *.h

linters: 
	clang-format -i *.cpp *.h

clang_check:
	clang-format -n *.cpp *.h
	clang-format -i *.cpp *.h


gcov_report: test
	lcov -t "Unit-tests of matrix" -o s21_matrix.info -c -d .
	genhtml -o $(REPORTDIR) s21_matrix.info
	open -a "Safari" ./$(REPORTDIR)/index.html

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./$(REPORTDIR) *.info ./*.info report matrix s21_matrix 
