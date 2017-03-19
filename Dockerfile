FROM golang:1.8 

RUN go get github.com/constabulary/gb/...

WORKDIR /project 
ADD . /project 

RUN gb build 
RUN gb test -v 