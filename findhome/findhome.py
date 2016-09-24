from flask import Flask
from flask import render_template
from flask import request

app = Flask(__name__)

@app.route("/")
def root():
    return render_template("index.html")

@app.route("/hello/")
@app.route("/hello/<name>")
def hello(name=None):
    return render_template('hello.html', name=name)


@app.route('/login/')
def login():
    return render_template('login.html')

@app.route('/dologin', methods=['POST'])
def dologin():
    print('.........xxxxxxxxxxxxxxx...........')
    if request.method == 'POST':
        print("Login happened :)")
    else:
        print("No login for you :(")
    return hello("COISA")

if __name__ == "__main__":
    print("Started main....")
    app.run()

