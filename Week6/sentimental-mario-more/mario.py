
height = 0

while height <= 0 or height > 8:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Invalid input. Please enter a valid integer.")

for i in range(1, height+1):
    print(" "*(height-i) + "#"*i + "  " + "#"*i)