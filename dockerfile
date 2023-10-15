FROM python:3

RUN mkdir APP
WORKDIR APP/

COPY . .

RUN pip3 install requirements.txt

EXPOSE 80
CMD "python3 main.py"