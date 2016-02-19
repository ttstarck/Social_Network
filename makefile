CXX=g++
# CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Werror -Wextra

BINARIES=tests
tests: SN_Tests.o Hashtable.o
	${CXX} $^ -o $@
run_tests: tests
	-./tests
clean:
	/bin/rm -f ${BINARIES} *.o
