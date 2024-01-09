FROM ubuntu:22.04


ENV PATH="${PATH}:/opt/bin"
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt install -y \
        mosquitto \
        mosquitto-clients \
        libmosquittopp1 \
        libmosquittopp-dev \
        build-essential \
        cmake \
        googletest \
        libgtest-dev \
        libgmock-dev \
        libtbb-dev \
        libcivetweb-dev \
        libcivetweb1 \
        less \
        vim \
        unzip \
        curl \
        doxygen && \
    #gtest build start - google test \
    mkdir /tmp/.build && \
    cd /tmp/.build && \
    cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/lib -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/ && \
    make && \
    cp /tmp/.build/lib/*.so* /usr/lib/x86_64-linux-gnu/ && \
    ldconfig && \
    rm -rf /tmp/.build && \
    #doxybook2 install - doxygen -> doxybook2 -> code docs in md format \
    mkdir /tmp/.doxy && \
    cd /tmp/.doxy && \
    curl -L -s -o doxybook2.zip https://github.com/matusnovak/doxybook2/releases/download/v1.5.0/doxybook2-linux-amd64-v1.5.0.zip && \
    unzip *.zip && \
    mv bin/* /usr/bin/ && \
    rm -rf /tmp/.doxy


COPY ./Makefile /opt/
COPY ./src /opt/src
COPY ./cfg/mosquitto.conf /etc/mosquitto/conf.d/
COPY ./cfg/Doxyfile /opt/
COPY ./cfg/doxybook.json /opt/

RUN cd /opt && \
    make -p /opt/build && \
    (make clean || exit 0) && \
    make && \
    make install && \
    cd /opt/ && \
    mkdir -p md && \
    (doxygen Doxyfile || exit 0) && \
    (doxybook2 --input doxygen/xml/ --output md || exit 0)

WORKDIR /opt/bin

CMD ["bash"]
