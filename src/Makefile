prefix=/opt
bindir=$(prefix)/bin
binary_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

CXX=g++
CXXFLAGS=-Og -ggdb -fno-sanitize-recover=all -fsanitize=address,alignment,undefined -Wall
OBJS=utils.o broker.o
EXECS= fps communication fmac eaic ccu aggregation navigation movement \
		situation extinguishing monitor utils_unittest
INCLUDE = -I/usr/include/ -I./
LDFLAGS:=$(LDFLAGS) -lmosquittopp -lgtest -pthread
TESTS=utils_unittest

.PHONY: clean uninstall

all: $(OBJS) $(patsubst %.cpp, %.out, $(addsuffix .cpp, $(EXECS))) tests

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< 

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(patsubst %.out, %.o, $@) -c $< 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(@:.out=) $(patsubst %.out, %.o, $@) $(OBJS)

tests: $(TESTS)
	$(binary_path)/$^

check:
	cppcheck *.cpp

format:
	clang-format -i *.cpp
	clang-format -i *.h

install:
	mkdir -p $(bindir)
	install $(EXECS) $(bindir)

clean:
	rm ${EXECS} ${OBJS} $(addsuffix .o, $(EXECS))

uninstall:
	cd  $(bindir) && rm {EXECS}
