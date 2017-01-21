FROM orangelang/llvm:3.8.0
RUN apt-get update
RUN apt-get -y install gcc g++

RUN mkdir /src
COPY . /src

RUN mkdir /build
WORKDIR /build
RUN cmake /src
RUN cmake --build .

# Remove unneeded packages, caches, and files
RUN rm -rf /build /src
RUN apt-get remove -y gcc g++
RUN apt autoremove -y
RUN rm -rf /var/lib/apt/lists/*
RUN rm -rf /usr/local/llvm
