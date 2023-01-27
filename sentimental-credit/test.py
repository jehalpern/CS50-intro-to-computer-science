# get user input, digit length, convert to int
c = input("Number: ")
n = len(c)
c = int(c)

def main(c, n):
#if 15 digits - AMEX
    if n == 15:
        count = 0

        #multiply every other digit by 2 starting with the 2nd to last digit and add to totaly count
        for i in [2, 4, 6, 8, 10, 12, 14]:
            temp = digit(c, i) * 2
            if temp < 10:
                count +=temp
            else:
                count += round((temp/10) - ((temp % 10)/10)) + (temp % 10)

        #add remaining digits to the total count
        for i in [1, 3, 5, 7, 9, 11, 13, 15]:
            temp = digit(c, i)
            count +=temp

        if (count % 10) == 0:
            print("AMEX\n")
        else:
            print("INVALID\n")

#if 13 digits - VISA
    if n == 13
        count = 0

        #multiply every other digit by 2 starting with the 2nd to last digit and add to totaly count
        for i in [2, 4, 6, 8, 10, 12]:
            temp = digit(c, i) * 2
            if temp < 10:
                count +=temp
            else:
                count += round((temp/10) - ((temp % 10)/10)) + (temp % 10)

        #add remaining digits to the total count
        for i in [1, 3, 5, 7, 9, 11, 13]:
            temp = digit(c, i)
            count +=temp

        if (count % 10) == 0:
            print("VISA\n")
        else:
            print("INVALID\n")

#16 digit visa or mastercard
    if n == 16
        count = 0

        #multiply every other digit by 2 starting with the 2nd to last digit and add to totaly count
        for i in [2, 4, 6, 8, 10, 12, 14, 16]:
            temp = digit(c, i) * 2
            if temp < 10:
                count +=temp
            else:
                count += round((temp/10) - ((temp % 10)/10)) + (temp % 10)

        #add remaining digits to the total count
        for i in [1, 3, 5, 7, 9, 11, 13, 15]:
            temp = digit(c, i)
            count +=temp

        if (count % 10) == 0:
            print("AMEX\n")
        else:
            print("INVALID\n")







#return specific digit where nth is the nth digit starting from the end
def digit(c, nth):
    y = ((c %(10**nth)/(10**(nth - 1)))) - (c % (10**(nth - 1))/ (10**(nth - 1)))
    return round(y)



main(c,n)
