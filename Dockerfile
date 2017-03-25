FROM golang:1.8 

WORKDIR /go/src/github.com/orange-lang/orange 
ADD . /go/src/github.com/orange-lang/orange 


RUN go get -t -v ./...
RUN go build 
RUN go test -v ./test/...