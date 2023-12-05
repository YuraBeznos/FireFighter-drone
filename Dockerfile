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
        less \
        vim

COPY ./src /opt/src
COPY ./cfg/mosquitto.conf /etc/mosquitto/conf.d/

RUN cd /opt/src && \
    (make clean || exit 0) && \
    make && \
    make install

WORKDIR /opt/bin

CMD ["bash"]
