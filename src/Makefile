TESTFLAGS = -lgtest -lpthread
GCCFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++ -pedantic
GCOVFLAGS = -fprofile-arcs -ftest-coverage
all: clean gcov_report

test: clean
	@clear
	@gcc -o test s21_matrix_oop.cc other_function.cc g_tests.cc  $(TESTFLAGS) $(GCCFLAGS)
	./test

test_for_gcov:
	@gcc -o test s21_matrix_oop.cc other_function.cc g_tests.cc $(TESTFLAGS) $(GCCFLAGS) $(GCOVFLAGS)
	./test

s21_matrix_oop.a:
	@gcc $(GCCFLAGS) -c s21_matrix_oop.cc other_function.cc
	ar rcs s21_matrix_oop.a s21_matrix_oop.o other_function.o
	ranlib s21_matrix_oop.a

test_leaks: test 
	@clear
	leaks -atExit -- ./test

gcov_report: test_for_gcov
	@lcov -t "./gcov" -o report.info --no-external -c -d . --ignore-errors mismatch --rc geninfo_unexecuted_blocks=1
	@genhtml -o report report.info
	@open ./report/index.html


style:
	@clang-format --style=google -n *.cc *.h

clean:
	@rm -rf test 
	@rm -rf *.o *.a *.out *.gcno *.gcda *.info *.gch test report gcov_report