number = input("Number: ")
cpy = int(number)
sum = 0
while cpy > 0:
    sum = sum + cpy % 10
    cpy = cpy//10
    sum = sum + ((cpy % 10)*2) % 10 + ((cpy % 10)*2)//10
    cpy = cpy//10

if sum % 10 == 0:
    if (len(number) == 16 or len(number) == 13) and int(number[0]) == 4:
        print("VISA")
    elif len(number) == 15 and (int(number[:2]) == 34 or int(number[:2]) == 37):
        print("AMEX")
    elif len(number) == 16 and (int(number[:2]) >= 51 and int(number[:2]) <= 55):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")


