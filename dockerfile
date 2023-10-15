FROM python:3

RUN mkdir APP
COPY . .

RUN pip3 install requirements.txt

CMD "python3 main.py"