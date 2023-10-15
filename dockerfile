FROM gcc:12.3

RUN mkdir APP
WORKDIR APP/

COPY . .

EXPOSE 80
CMD "./main.out"