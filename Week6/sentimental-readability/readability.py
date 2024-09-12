text = input("Text: ")  # Get Input from user
noW = len(text.split())  # Calculating number of words in text
noL = len([ele for ele in text if ele.isalpha()])   # calculating number of Letters in text
noS = text.count('.') + text.count('!') + text.count('?')   # Calculating number of sentences in text

L = (noL/noW)*100   # Calculating number of letters per 100 words
S = (noS/noW)*100   # Calculating number of sentences per 100 words

index = (0.0588 * L) - (0.296 * S) - 15.8   # Calculating index

if index < 1:
    print("Before Grade 1")  # print if index smaller than 1
elif index >= 16:
    print("Grade 16+")  # print if index greater than 16
else:
    print("Grade " + str(round(index)))  # print if in range of 1-16