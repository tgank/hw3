CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

OBJS := llrec-test.o llrec.o

all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

llrec-test: $(OBJS)
  $(CXX) $(CXXFLAGS) -o $@ $^

llrec-test.o: llrec-test.cpp llrec.h
  $(CXX) $(CXXFLAGS) -c $

llrec.o: llrec.cpp llrec.h
  $(CXX) $(CXXFLAGS) -c $

valgrind: llrec-test
  $(VALGRIND) ./llrec-test

clean:
  rm -f *.o rh llrec-test *~

.PHONY: clean all valgrind