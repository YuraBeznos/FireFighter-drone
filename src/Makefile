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
		rm -rf /tmp/.build && \
		mkdir /tmp/.doxy && \
		cd /tmp/.doxy && \
		curl -L -s -o doxybook2.zip https://github.com/matusnovak/doxybook2/releases/download/v1.5.0/doxybook2-linux-amd64-v1.5.0.zip && \
		unzip *.zip && \
		mv bin/* /usr/bin/ && \
		rm -rf /tmp/.doxy

prepare-20:
		sudo rm -Rf /tmp/firefighter-drone && \
		mkdir -p /tmp/firefighter-drone/gtest && \
		mkdir -p /tmp/firefighter-drone/doxy && \
		mkdir -p /tmp/firefighter-drone/civetweb && \
		mkdir -p /tmp/firefighter-drone/ && \
		sudo apt-get update && \
		sudo apt install -y \
		mosquitto-clients \
		libmosquittopp1 \
		libmosquittopp-dev \
		build-essential \
		cmake googletest \
		libgtest-dev \
		libgmock-dev \
		libtbb-dev \
		unzip \
		curl \
		doxygen && \
		cd /tmp/firefighter-drone/gtest && \
		cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/lib -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/ && \
		make && \
		sudo cp /tmp/firefighter-drone/gtest/lib/*.so* /usr/lib/x86_64-linux-gnu/ && \
		sudo ldconfig && \
		cd /tmp/firefighter-drone/doxy && \
		curl -L -s -o doxybook2.zip https://github.com/matusnovak/doxybook2/releases/download/v1.5.0/doxybook2-linux-amd64-v1.5.0.zip && \
		unzip *.zip && \
		sudo mv bin/* /usr/bin/ && \
		cd /tmp/firefighter-drone/civetweb && \
		curl -L -s -o v1.15.tar.gz https://github.com/civetweb/civetweb/archive/refs/tags/v1.15.tar.gz && \
		tar xzf v1.15.tar.gz && \
		cd civetweb-1.15 && \
		mkdir .build && \
		cd .build && \
		cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=None -DCMAKE_INSTALL_SYSCONFDIR=/etc -DCMAKE_INSTALL_LOCALSTATEDIR=/var -DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON -DCMAKE_FIND_USE_PACKAGE_REGISTRY=OFF -DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON -DFETCHCONTENT_FULLY_DISCONNECTED=ON -DCMAKE_INSTALL_RUNSTATEDIR=/run -DCMAKE_SKIP_INSTALL_ALL_DEPENDENCY=ON "-GUnix Makefiles" -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_INSTALL_LIBDIR=lib/x86_64-linux-gnu -DCMAKE_BUILD_TYPE=None -DCIVETWEB_BUILD_TESTING=OFF -DCIVETWEB_SOVERSION=1 -DCIVETWEB_ENABLE_CXX=ON -DBUILD_SHARED_LIBS=ON -DCIVETWEB_ENABLE_WEBSOCKETS=ON .. && \
		make -j4 "INSTALL=install --strip-program=true" VERBOSE=1 && \
		sudo make install && \
		sudo rm -rf /tmp/firefighter-drone

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

