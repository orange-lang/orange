FROM ubuntu:xenial
RUN apt-get update
RUN apt-get -y install gcc g++ cmake make

RUN mkdir /src
ADD . /src

RUN mkdir /build
WORKDIR /build
RUN cmake /src
RUN make all
