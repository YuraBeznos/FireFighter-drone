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
        less \
        vim && \
    mkdir /tmp/.build &&\
    cd /tmp/.build && \
    cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/lib -DCMAKE_BUILD_TYPE=RELEASE /usr/src/gtest/ && \
    make && \
    cp /tmp/.build/lib/*.so* /usr/lib/x86_64-linux-gnu/ && \
    ldconfig && \
    rm -rf /tmp/.build

COPY ./src /opt/src
COPY ./cfg/mosquitto.conf /etc/mosquitto/conf.d/

RUN cd /opt/src && \
    (make clean || exit 0) && \
    make && \
    make install

WORKDIR /opt/bin

CMD ["bash"]
