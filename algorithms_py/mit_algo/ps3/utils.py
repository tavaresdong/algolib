import sys

def read_list(filename):
    """
    Reads and returns a list of numbers from the file filename.
    """
    # Read the input file
    try:
        fp = open(filename)
        content = fp.read()
    except IOError:
        print ("Error opening or reading input file: ", filename)
        sys.exit()
    # Convert the input into words
    words = content.split()
    # Convert all words into integers
    try:
        numbers = list(map(int, words))
    except ValueError:
        print ("Error: the input file doesn't consist of integers")
        sys.exit()
    # make sure the file is not empty
    if len(words) == 0:
        print ("Error: the input file is empty")
        sys.exit()
    return numbers

def read_integer(filename):
    """
    Reads and returns an integer from the file filename.
    """
    # Read the input file
    try:
        fp = open(filename)
        content = fp.read()
    except IOError:
        print ("Error opening or reading input file: ", filename)
        sys.exit()
    # Convert contents into an integer
    try:
        number = int(content)
    except ValueError:
        print ("Error: the input file doesn't consist of a single integer")
        sys.exit()
    return number
