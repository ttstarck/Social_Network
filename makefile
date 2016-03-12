#
# makefile
# Social_Network
#

CXX=g++
# CXX=clang++

CXXFLAGS = -g -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter  -Wno-unused-variable #added the last so I wouldn't get the unused parameter/variable error

BINARIES=tests main btree
tests: SN_Tests.o Hashtable.o FSeeker.o
	${CXX} $^ -o $@
run_tests: tests
	-./tests
btree: BTree.o BT_Tests.o
	${CXX} $^ -o $@
run_bt: btree
	-./btree
main: main.o FSeeker.o Hashtable.o BTree.o
	${CXX} $^ -o $@
run_main: main
	-./main
clean:
	/bin/rm -f ${BINARIES} *.o ProfileData.txt
