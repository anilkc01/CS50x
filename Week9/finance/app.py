import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, is_int

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(CASE WHEN action = 'bought' THEN quantity WHEN action = 'sold' THEN - quantity ELSE 0 END) AS shares FROM transactions WHERE userid = ? GROUP BY symbol HAVING shares > 0;",session.get("user_id"))

    holdings = []
    total_stock_value = 0
    for row in rows:
        symbol = row["symbol"]
        shares = row["shares"]


        price = lookup(symbol)["price"]
        total_stock_value += shares*price

        holdings.append({
            "symbol": symbol,
            "shares": shares,
            "price": price,
            "total": shares*price
        })
    cash = db.execute("SELECT cash FROM users WHERE id = ?",session.get("user_id"))


    return render_template("index.html",holdings=holdings,total_stock_value=total_stock_value,cash=cash[0]["cash"],usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    symbol = None
    price = None
    shares = None
    total = None

    if request.method == "POST":
            symbol = request.form["symbol"]

            try:
                shares = int(request.form["shares"])
                if int(shares) <= 0 :
                    return apology("Invalid shares amount",400)
            except ValueError:
                return apology("Invalid shares input",400)

            quote = lookup(symbol)

            if quote:
                symbol = quote["symbol"]
                price = quote["price"]
                total = price * shares

            else:
                return apology("symbol not found",400)

            cash = db.execute("SELECT cash FROM users WHERE id = ?",session.get("user_id"))

            if float(cash[0]["cash"]) < total:
                return apology("Not Enough cash",403)
            else:
                db.execute("INSERT INTO transactions (userid,symbol,price,quantity, action) VALUES (?,?,?,?,?)", session.get("user_id"),symbol,price,shares,"bought")
                updatedCash = cash[0]["cash"] - total
                db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedCash, session.get("user_id"))
                flash(f"Bought {request.form["shares"]} shares of {request.form["symbol"]} for {usd(total)}, Updated cash: {usd(updatedCash)}")
                return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM transactions WHERE userid = ?",session.get("user_id"))
    records = []
    for row in rows:
        symbol=row["symbol"]
        shares=row["quantity"]
        price=row["price"]
        action=row["action"]
        time=row["time"]

        records.append({
            "symbol": symbol,
            "shares": shares,
            "price": price,
            "total": price*shares,
            "action": action.upper(),
            "time": time
        })
    return render_template("history.html",records=records,usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    symbol = None
    price = None
    if request.method == "POST":

        check = request.form["symbol"]
        if len(check) == 1:
            return apology("Please Enter the symbol",400)
        quote = lookup(check)
        print(quote)

        if quote:
            symbol = quote["symbol"]
            price = quote["price"]

        else:
            return apology("No symbol found",400)

        return render_template("quote.html", symbol = symbol, price = price, usd=usd)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":
        row = db.execute("SELECT * FROM users WHERE username = ?",request.form.get("username"))
        if not request.form.get("username"):
            return apology("must provide User Name", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password didn't match", 400)
        elif len(row) == 1:
            return apology("Username already exists",400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)",request.form.get("username"),generate_password_hash(request.form.get("password")))
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbol = None
    price = None
    shares = None
    total = None

    if request.method == "POST":
            symbol = request.form["symbol"]
            shares = request.form["shares"]

            if not symbol:
                return apology("MISSING SYMBOL", 400)

            if not shares or not shares.isdigit():
                return apology("INVALID SHARES", 400)
            if not is_int(shares):
                return apology("Fractional shares not supported", 400)
            if int(shares) <= 0:
                return apology("Share count must be positive", 400)

            quote = lookup(symbol)

            print(quote)

            if quote:
                symbol = quote["symbol"]
                price = quote["price"]
                total = price * int(shares)
                print(total)
            else:
                return apology("symbol not found",400)


            holds = db.execute("SELECT IFNULL(SUM(CASE WHEN action = 'bought' THEN quantity WHEN action = 'sold' THEN -quantity ELSE 0 END), 0) AS shares FROM transactions WHERE userid = ? AND symbol = ?", session.get("user_id"), symbol.upper())[0]['shares']
            cash = db.execute("SELECT cash FROM users WHERE id = ?",session.get("user_id"))

            if int(shares) > holds:
                return apology("No enough holdings",400)
            else:
                db.execute("INSERT INTO transactions (userid,symbol,price,quantity, action) VALUES (?,?,?,?,?)", session.get("user_id"),symbol,price,shares,"sold")
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash[0]["cash"] + total, session.get("user_id"))
                return redirect("/")


    else:
        user_portfolio = db.execute("SELECT symbol, SUM(CASE WHEN action = 'bought' THEN quantity WHEN action = 'sold' THEN - quantity ELSE 0 END) AS shares FROM transactions WHERE userid = ? GROUP BY symbol HAVING shares > 0;",session.get("user_id"))
        print(user_portfolio)
        return render_template("sell.html", user_portfolio=user_portfolio)

@app.route("/cpw", methods=["GET", "POST"])
@login_required
def cpw():
    """change password"""

    if request.method == "POST":
        old = request.form["oldpassword"]
        new = request.form["newpassword"]
        conf = request.form["confirmation"]
        if new != conf:
            return apology("password doesnot match with confirmation",403)
        elif old == new:
            return apology("Enter different from old password",403)
        else:
            rows = db.execute("SELECT hash FROM users WHERE id = ?", session.get("user_id"))
            if check_password_hash(rows[0]["hash"],old):
                db.execute("UPDATE users SET hash = ? WHERE id = ?",generate_password_hash(new),session.get("user_id"))
                session.clear()
                return redirect("/")
            else:
                return apology("Incorrect Old Password")

    return render_template("cpw.html")
