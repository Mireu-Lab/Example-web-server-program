FROM python:3

RUN mkdir APP
COPY . .

RUN pip3 install -r requirements.txt

RUN "python3 main.py"