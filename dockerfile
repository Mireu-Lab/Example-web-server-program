FROM node:20

RUN mkdir APP/
WORKDIR APP/

COPY . .

RUN npm i
CMD "nodejs main.js"