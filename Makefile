prefix=/opt
bindir=$(prefix)/bin
binary_path := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
src := $(binary_path)src
build := $(binary_path)build

CXX=g++
CXXFLAGS=-Og -ggdb -fno-sanitize-recover=all -fsanitize=address,alignment,undefined -Wall

OBJS=$(build)/utils.o \
	 $(build)/broker.o

EXECS=$(build)/fps \
	  $(build)/communication \
	  $(build)/fmac \
	  $(build)/eaic \
	  $(build)/ccu \
	  $(build)/aggregation \
	  $(build)/navigation \
	  $(build)/movement \
	  $(build)/situation \
	  $(build)/extinguishing \
	  $(build)/monitor \
	  $(build)/utils_unittest \
	  $(build)/monitor_unittest

INCLUDE = -I/usr/include/ -I$(src)/

LDFLAGS:=$(LDFLAGS) -lmosquittopp -lgtest -pthread -lcivetweb-cpp -lcivetweb

TESTS=$(build)/utils_unittest \
	  $(build)/monitor_unittest

SHELL=/bin/bash

.PHONY: docs e2e-clean docker-compose-stop clean uninstall
.NOTPARALLEL: e2e-tests

all: $(OBJS) $(patsubst %.cpp, %.out, $(addsuffix .cpp, $(EXECS))) unittests

$(build):
	mkdir -p $@

$(build)/%.o: $(src)/%.cpp $(src)/%.h | $(build)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< 

$(build)/%.out: $(src)/%.cpp | $(build)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(patsubst %.out, %.o, $@) -c $< 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE) -o $(@:.out=) $(patsubst %.out, %.o, $@) $(OBJS)

policy-tests: unittests

unittests:
	$(foreach unittest, $(wildcard $(build)/*unittest), $(unittest);)

check:
	cppcheck $(src)/*.cpp

format:
	clang-format -i $(src)/*.cpp
	clang-format -i $(src)/*.h

install:
	mkdir -p $(bindir)
	install $(EXECS) $(bindir)

clean:
	@rm ${EXECS} ${OBJS} $(addsuffix .o, $(EXECS)) || true

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

mosquitto: docker
	docker run --rm -ti ffd mosquitto -v -c /etc/mosquitto/conf.d/mosquitto.conf

docker:
	docker build ./ -t ffd

docker-clean:
	docker ps -a -q |xargs docker rm

run: docker
	docker-compose up

docs:
	doxygen cfg/Doxyfile
	doxybook2 -c cfg/doxybook.json --input doxygen/xml/ --output docs

docker-compose-stop:
	docker-compose stop

docker-compose-up: docker docker-compose-stop
	docker-compose up -d

e2e-prepare: docker-compose-up

e2e-tests: e2e-prepare e2e-test-a e2e-test-b
	docker-compose stop

tests: e2e-tests

prepare:
		sudo rm -Rf /tmp/firefighter-drone && \
		mkdir -p /tmp/firefighter-drone/gtest && \
		mkdir -p /tmp/firefighter-drone/doxy && \
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
		cd /tmp/firefighter-drone/gtest && \
		cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/lib -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/ && \
		make && \
		sudo cp /tmp/firefighter-drone/gtest/lib/*.so* /usr/lib/x86_64-linux-gnu/ && \
		sudo ldconfig && \
		cd /tmp/firefighter-drone/doxy && \
		curl -L -s -o doxybook2.zip https://github.com/matusnovak/doxybook2/releases/download/v1.5.0/doxybook2-linux-amd64-v1.5.0.zip && \
		unzip *.zip && \
		sudo mv bin/* /usr/bin/ && \
		sudo rm -rf /tmp/firefighter-drone

prepare-20:
		sudo rm -Rf /tmp/firefighter-drone && \
		mkdir -p /tmp/firefighter-drone/gtest && \
		mkdir -p /tmp/firefighter-drone/doxy && \
		mkdir -p /tmp/firefighter-drone/civetweb && \
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


