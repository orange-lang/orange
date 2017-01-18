FROM orangelang/llvm:3.6.2
RUN apt-get update
RUN apt-get -y install gcc-4.9 g++-4.9 bison flex

RUN mkdir /src
COPY . /src

RUN mkdir /build
WORKDIR /build
RUN cmake /src -DLLVM_DIR=/usr/local/llvm/share/llvm/cmake -DCMAKE_CXX_COMPILER=g++-4.9 -DCMAKE_C_COMPILER=gcc-4.9
RUN cmake --build .
RUN cmake --build . --target install

# Remove unneeded packages, caches, and files
RUN rm -rf /build /src
RUN apt-get remove -y gcc g++
RUN apt autoremove -y
RUN rm -rf /var/lib/apt/lists/*
RUN rm -rf /usr/local/llvm

ENTRYPOINT ["orange"]
