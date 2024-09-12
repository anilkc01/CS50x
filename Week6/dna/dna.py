import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) !=3:
        print("wrong command line argument")
        sys.exit(0)

    # TODO: Read database file into a variable
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        fieldnames = reader.fieldnames

        # Initialize an empty dictionary to store the data
        data_dict = {}
        # Iterate over each row in the CSV file
        for row in reader:
            # Extract the name from the row
            name = row['name']
            # Remove the name from the row dictionary
            del row['name']
            # Store the row dictionary in the main dictionary
            data_dict[name] = row

      # print(data_dict['Harry']['AGATC'])

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        sequence = file.readline()

    # TODO: Find longest match of each STR in DNA sequence
    longestMatch = {}
    for item in fieldnames[1:]:
        longestMatch[item] = longest_match(sequence, item)

    # TODO: Check database for matching profiles
    for name, item_value_dict in data_dict.items():
        isMatch = False
        for item, value in item_value_dict.items():
            if int(value) != int(longestMatch.get(item)):
                isMatch = False
                break
        else:
            isMatch = True
        if isMatch:
            print(name)
            return 1
        
    print("No Match")
    return 1







def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
