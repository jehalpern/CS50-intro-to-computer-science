# get user input, digit length, convert to int, and set count to 0
c = input("Number: ")
n = len(c)
c = int(c)
count = 0

# calculate the "count" given by the algorithm
def count_func(c, n, count):

    # multiply every other digit by 2 starting with the 2nd to last digit and add to total count
    for i in [2, 4, 6, 8, 10, 12, 14, 16]:
        if (n == 16) or (n == 15 and i != 16) or (n == 13 and i != 16 and i != 14):
            temp = digit(c, i) * 2
            if temp < 10:
                count += temp
            else:
                count += round((temp/10) - ((temp % 10)/10)) + (temp % 10)

    # add remaining digits to the total count
    for i in [1, 3, 5, 7, 9, 11, 13, 15]:
        if (n == 16) or (n == 15) or (n == 13 and i != 15):
            temp = digit(c, i)
            count += temp

    return count

# return specific digit where nth is the nth digit starting from the end
def digit(c, nth):
    y = ((c % (10**nth)/(10**(nth - 1)))) - (c % (10**(nth - 1)) / (10**(nth - 1)))
    return round(y)

# print the result
def print_result(c, n):

    count_final = count_func(c, n, count)

    if (count_final % 10 != 0) or (n < 13):
        print("INVALID")
    elif n == 15 and digit(c, 15) == 3 and (digit(c, 14) == 4 or digit(c, 14) == 7):
        print("AMEX")
    elif (n == 16 and digit(c, 16) == 4) or n == 13:
        print("VISA")
    elif n == 16 and digit(c, 16) == 5 and digit(c, 15) < 6:
        print("MASTERCARD")
    else:
        print("INVALID")


print_result(c, n)