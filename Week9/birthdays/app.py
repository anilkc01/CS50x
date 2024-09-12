import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if  not name :
            return("Opps !! you seem to miss some required field")
        elif int(month) < 1 or int(month) > 12:
            return("Please enter the month with the range of 1-12 as our calendar only has 12 months.")
        elif int(day) < 1 or int(day) > 31:
            return("Please enter the day with the range of 1-31.")
        else:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?,?,?)", name, month, day)
            return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        list = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", list=list)


