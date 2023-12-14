prefix=/opt
bindir=$(prefix)/bin
binary_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

CXX=g++
CXXFLAGS=-Og -ggdb -fno-sanitize-recover=all -fsanitize=address,alignment,undefined -Wall
OBJS=utils.o broker.o
EXECS= fps communication fmac eaic ccu aggregation navigation movement \
		situation extinguishing monitor utils_unittest monitor_unittest
INCLUDE = -I/usr/include/ -I./
LDFLAGS:=$(LDFLAGS) -lmosquittopp -lgtest -pthread -lcivetweb-cpp -lcivetweb
TESTS=utils_unittest monitor_unittest

SHELL=/bin/bash
.PHONY: clean uninstall

all: $(OBJS) $(patsubst %.cpp, %.out, $(addsuffix .cpp, $(EXECS))) unittests

prepare:
	sudo apt install -y \
		mosquitto-clients \
		libmosquittopp1 \
		libmosquittopp-dev \
		build-essential \
		cmake googletest \
		libgtest-dev \
		libgmock-dev \
		libtbb-dev \
		libcivetweb-dev \
		libcivetweb1 \
		unzip \
		curl \
		doxygen && \
		mkdir /tmp/.build && \
		cd /tmp/.build && \
		cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/lib -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/ && \
		make && \
		cp /tmp/.build/lib/*.so* /usr/lib/x86_64-linux-gnu/ && \
		ldconfig && \
		rm -rf /tmp/.build

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< 

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(patsubst %.out, %.o, $@) -c $< 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(@:.out=) $(patsubst %.out, %.o, $@) $(OBJS)

policy-tests: unittests

unittests:
	$(foreach unittest, $(wildcard $(binary_path)*unittest), $(unittest);)

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

e2e-test-a:
	echo "Test e2e - try start authentic task A"
	while true ; do \
		((++counter)); \
		curl -s "http://localhost:8081/api"; \
		exit_code=$$?; \
		if [ $${exit_code} -eq 0 ] ; then \
			echo "FPS is accessible"; \
			break; \
		fi; \
		if [ $${counter} -gt 60 ] ; then \
			echo "Test failed (FPS not accessible, waiting timeout in 60 secs is reached)"; \
			exit 1; \
		fi; \
		echo "Waiting..."; \
		sleep 1; \
	done; \
	curl -s "http://localhost:8081/api?command=start&task=A" 1>/dev/null && echo "Start Task A";\
	exit_code=$$?; \
	if [ $${exit_code} -ne 0 ] ; then \
		echo "Not able connect to fps on localhost:8081"; \
		exit 1; \
	fi; \
	sleep 2; \
	while true ; do \
		((++counter)); \
		curl -s "http://localhost:8081/api?tasks_log=true" |tail -1 |grep "Task A: started"; \
		exit_code=$$?; \
		if [ $${exit_code} -eq 0 ] ; then \
			echo "Test completed successfully"; \
			break; \
		fi; \
		if [ $${counter} -gt 60 ] ; then \
			echo "Test failed (waiting timeout in 60 secs is reached)"; \
			exit 1; \
		fi; \
		echo "Waiting..."; \
		sleep 1; \
	done;

e2e-test-b:
	echo "Test e2e - try to start not_authentic task B"
	while true ; do \
		((++counter)); \
		curl -s "http://localhost:8081/api"; \
		exit_code=$$?; \
		if [ $${exit_code} -eq 0 ] ; then \
			echo "FPS is accessible"; \
			break; \
		fi; \
		if [ $${counter} -gt 60 ] ; then \
			echo "Test failed (FPS not accessible, waiting timeout in 60 secs is reached)"; \
			exit 1; \
		fi; \
		echo "Waiting..."; \
		sleep 1; \
	done; \
	curl -s "http://localhost:8081/api?command=start&task=B" 1>/dev/null && echo "Start Task B";\
	exit_code=$$?; \
	if [ $${exit_code} -ne 0 ] ; then \
		echo "Not able connect to fps on localhost:8081"; \
		exit 1; \
	fi; \
	sleep 2; \
	while true ; do \
		((++counter)); \
		curl -s "http://localhost:8081/api?tasks_log=true" |tail -1 |grep "Task B: not authentic"; \
		exit_code=$$?; \
		if [ "$$exit_code" -eq 0 ] ; then \
			echo -e "Test completed successfully"; \
			break; \
		fi; \
		if [ $${counter} -gt 60 ] ; then \
			echo "Test failed (waiting timeout in 60 secs is reached)"; \
			exit 1; \
		fi; \
		echo "Waiting..."; \
		sleep 1; \
	done;

