FROM orangelang/llvm:3.8.0
RUN apt-get update
RUN apt-get -y install gcc g++

RUN mkdir /src
ADD . /src

RUN mkdir /build
WORKDIR /build
RUN cmake /src -DUSE_SYSTEM_LLVM=True
RUN cmake --build .
RUN cmake --build . --target install
RUN rm -rf /build /src

RUN apt-get remove -y gcc g++ 
RUN apt autoremove -y
RUN rm -rf /var/lib/apt/lists/*
