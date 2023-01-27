    userInfo = session_key()
    historyTitle = userInfo["historyTitle"]
    history = db.execute("SELECT symbol, shares, price, cost FROM ?", historyTitle)

    #pass updated values to /index
    return render_template("/history.html", history=history)
