FROM orangelang/llvm:3.8.0
RUN apt-get update
RUN apt-get -y install gcc g++

RUN mkdir /src
ADD . /src

RUN mkdir /build
WORKDIR /build
RUN cmake /src -DUSE_SYSTEM_LLVM=True -DLLVM_DIR=/usr/local/llvm/share/llvm/cmake
RUN cmake --build .
RUN cmake --build . --target install
RUN rm -rf /build /src

# Remove unneeded packages, caches, and files
RUN apt-get remove -y gcc g++ 
RUN apt autoremove -y
RUN rm -rf /var/lib/apt/lists/*
RUN rm -rf /usr/local/llvm
