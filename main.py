from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

while True:
    app.run("0.0.0.0", 1080, debug=True)