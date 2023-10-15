FROM python:3

RUN mkdir APP
WORKDIR APP/

COPY . .

RUN pip3 install -r requirements.txt

EXPOSE 80
RUN "python3 main.py"