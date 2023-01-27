import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1

    # TODO: Read database file into a variable
    data = open(sys.argv[1], "r")
    data_read = csv.reader(data, delimiter=',')

    # get dna sequences and # of sequences from 1st row of csv
    row1 = next(data_read)
    count = len(row1)

    # TODO: Read DNA sequence file into a variable
    seq = open(sys.argv[2], "r")
    r_seq = seq.read()

    # TODO: Find longest match of each STR in DNA sequence and append to list
    seq_l = [0, 0, 0, 0, 0, 0, 0, 0]
    for i in range(count - 1):
        seq_l[i] = longest_match(r_seq, row1[i+1])

    # TODO: Check database for matching profiles
    for row in data_read:
        matches = 0
        for i in range(count - 1):
            if int(row[i+1]) == seq_l[i]:
                matches += 1
        if matches == count - 1:
            print(row[0])
            return

    print("No Match\n")
    return


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
