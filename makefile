#
# makefile
# Social_Network
#

CXX=g++
# CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Werror -Wextra

BINARIES=tests, main
tests: SN_Tests.o Hashtable.o
	${CXX} $^ -o $@
run_tests: tests
	-./tests
main: main.o
	${CXX} $^ -o $@
run_main: main
	-./main
clean:
	/bin/rm -f ${BINARIES} *.o
