try:
    n = int(input("Height: "))
except:
    n = int(input("Height: "))

while (n < 1 or n > 8):
    n = int(input("Height: "))

for i in range(n + 1):
    if i != 0:
        print(" " * (n - i), "#" * i, "  ", "#" * i, sep='')