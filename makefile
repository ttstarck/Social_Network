#
# makefile
# Social_Network
#

CXX=g++
# CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter  #added the last so I wouldn't get the unused parameter error

BINARIES=tests, main
tests: SN_Tests.o Hashtable.o FSeeker.o
	${CXX} $^ -o $@
run_tests: tests
	-./tests
main: main.o
	${CXX} $^ -o $@
run_main: main
	-./main
clean:
	/bin/rm -f ${BINARIES} *.o
