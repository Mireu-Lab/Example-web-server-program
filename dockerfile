FROM golang:1.21

RUN mkdir APP/
WORKDIR APP/

COPY . .

CMD "./main"