# get text
text = input("Text: ")

# variables total letters, total words, total sentences
lttr = 0
wrds = 1
snt = 0

# fill variables
for element in text:
    if (element >= 'a' and element <= 'z') or (element >= 'A' and element <= 'Z'):
        lttr += 1
    elif element == " ":
        wrds += 1
    elif element == "." or element == "?" or element == "!":
        snt += 1


# calc average number of letters per 100 words
l = (lttr/wrds) * 100

# calc average number of sentences per 100 words
s = 100 / (wrds/snt)

index = round(0.0588 * l - 0.296 * s - 15.8)
print(lttr, wrds, snt)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")