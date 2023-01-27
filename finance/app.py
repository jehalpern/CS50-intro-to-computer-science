import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    userInfo = session_key()
    portfolioTitle = userInfo["portfolioTitle"]
    portfolio = db.execute("SELECT symbol, shares FROM ?", portfolioTitle)
    rows = db.execute("SELECT COUNT (symbol) FROM ?", portfolioTitle)
    rows = rows[0]['COUNT (symbol)']

    # loop through table and update values and price
    for i in range(rows):
        shares = portfolio[i]["shares"]
        stock = lookup(portfolio[i]["symbol"])
        symbolCurrent = stock["symbol"]
        price = stock["price"]
        value = round(shares * price)
        db.execute("UPDATE ? SET price = ?, value = ? WHERE symbol = ?", portfolioTitle, price, value, symbolCurrent)

    # pass updated values to /index
    portfolioTable = db.execute("SELECT symbol, shares, price, value FROM ?", portfolioTitle)
    accountBalance = db.execute("SELECT cash FROM users WHERE username = ?", userInfo["userName"])
    return render_template("/index.html", portfolioTable=portfolioTable, accountBalance=accountBalance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # POST request
    if request.method == "POST":
        # error check
        ticker = request.form.get("symbol")
        shares = float(request.form.get("shares"))
        if not ticker:
            return apology("Please enter symbol and shares")
        

        else:
            # api call
            stock = lookup(ticker)

            # error check
            if stock == None:
                return apology("invalid symbol")
            else:
                symb = stock["symbol"]
                price = stock["price"]
                cost = price * shares

                # access user info
                userInfo = session_key()
                userName = userInfo["userName"]
                userId = userInfo["userId"]
                historyTitle = userInfo["historyTitle"]
                portfolioTitle = userInfo["portfolioTitle"]

                # check for sufficient funds, then update database
                funds = userInfo["cashBalance"]
                if funds > cost:
                    # calc new cash balance
                    updated_balance = funds - cost

                    # USERS DB: update users db with new cash balance
                    db.execute("UPDATE users SET cash = ? WHERE username=?", updated_balance, userInfo['userName'])

                    # HISTORY DB:insert new transaction into history db
                    db.execute("INSERT INTO ? (id, symbol, shares, price, cost) VALUES (?, ?, ?, ?, ?)", historyTitle, userId, symb, shares, price, cost)

                    # PORTFOLIO DB: update portfolio
                    existingShares = db.execute("SELECT shares FROM ? WHERE symbol=?", portfolioTitle, symb)
                    value = db.execute("SELECT value FROM ? WHERE symbol=?", portfolioTitle, symb)
                    if existingShares:
                        newShares = existingShares[0]['shares'] + shares
                        db.execute("UPDATE ? SET shares = ? WHERE symbol = ?", portfolioTitle, newShares, symb)
                        return redirect("/")
                    else:
                        db.execute("INSERT INTO ? (id, symbol, shares, value) VALUES (?, ?, ?, ?)", portfolioTitle, userId, symb, shares, cost)
                        return redirect("/")

                else:
                    return apology("insufficient funds")


    # GET request
    else:
        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userInfo = session_key()
    historyTitle = userInfo["historyTitle"]
    history = db.execute("SELECT symbol, shares, price, cost FROM ?", historyTitle)

    # pass updated values to /index
    return render_template("/history.html", history=history)
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    # POST request
    if request.method == "POST":
        # use api to lookup symbol
        ticker = request.form.get("symbol")
        stock = lookup(ticker)

        # error check
        if stock == None:
           return apology("invalid symbol")

        # display stock info
        else:
            name = stock["name"]
            price = float(stock["price"])
            return render_template("/quote.html", name=name, price=price)


    # GET request
    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # POST request
    if request.method == "POST":
        u_name = request.form.get("username")
        password = request.form.get("password")
        re_password = request.form.get("confirmation")

        # check for errors
        # username exists
        if not u_name:
            return apology("must provide username", 400)
        # password exists
        elif not password or not re_password:
            return apology("please enter password then confirm passowrd", 400)
        # password matches confirmation password
        elif password != re_password:
            return apology("confirmation does not match password", 400)
        # query user db for unique username confirmation
        rows = db.execute("SELECT username FROM users WHERE username = ?", (u_name))
        if len(rows) != 0:
            return apology("Sorry, username is taken")

        # insert new user and hashed password into users db, create a transaction db specific to the user, log in new user
        else:
            h_password = generate_password_hash(password)
            history_db = u_name + "_history"
            portfolio_db = u_name + "_portfolio"
            db.execute("INSERT INTO users(username, hash) VALUES(?)", (u_name, h_password))
            id = db.execute("SELECT id FROM users WHERE username= ?", u_name)
            db.execute("CREATE TABLE ? (id INTEGER, symbol TEXT, shares INTEGER, price NUMERIC, cost NUMERIC)", history_db)
            db.execute("CREATE TABLE ? (id INTEGER, symbol TEXT, shares INTEGER, price NUMERIC, value NUMERIC)", portfolio_db)
            session["user_id"] = id
            return render_template("login.html")

    # GET request
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # POST request
    if request.method == "POST":
        # error check
        ticker = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        if not ticker or not shares or shares <= 0:
            return apology("Please enter symbol and shares")

        else:
            # api call
            stock = lookup(ticker)

            # error check
            if stock == None:
                return apology("invalid symbol")
            else:
                symb = stock["symbol"]
                price = stock["price"]
                cost = price * shares

                # access user info
                userInfo = session_key()
                userName = userInfo["userName"]
                userId = userInfo["userId"]
                historyTitle = userInfo["historyTitle"]
                portfolioTitle = userInfo["portfolioTitle"]
                cash = userInfo["cashBalance"]

                # check for sufficient shares, then update database
                existingShares = db.execute("SELECT shares FROM ? WHERE symbol=?", portfolioTitle, symb)
                existingShares = existingShares[0]["shares"]
                if existingShares >= shares:
                    # calc new cash balance
                    new_balance = cash + cost
                    updated_shares = existingShares - shares
                    share_subtract = shares * (-1)

                    # USERS DB: update users db with new cash balance
                    db.execute("UPDATE users SET cash = ? WHERE username=?", new_balance, userName)

                    # HISTORY DB:insert new transaction into history db
                    db.execute("INSERT INTO ? (id, symbol, shares, price, cost) VALUES (?, ?, ?, ?, ?)", historyTitle, userId, symb, share_subtract, price, cost)

                    # PORTFOLIO DB: update portfolio
                    db.execute("UPDATE ? SET shares = ? WHERE symbol = ?", portfolioTitle, updated_shares, symb)

                    return redirect("/")

                else:
                    return apology("insufficient shares")


    # GET request
    else:
        return render_template("/sell.html")



# returns a dictionary of current user's db items
def session_key():
    userId = session.get("user_id")
    # userId = userId[0]["id"]
    userName = db.execute("SELECT username FROM users WHERE id = ?", userId)
    userCash = db.execute("SELECT cash FROM users WHERE id = ?", userId)
    historyTitle = userName[0]["username"] + "_history"
    portfolioTitle = userName[0]["username"] + "_portfolio"

    return {
        "userName": userName[0]["username"],
        "userId": userId,
        "historyTitle": historyTitle,
        "portfolioTitle": portfolioTitle,
        "cashBalance": userCash[0]["cash"]
    }

