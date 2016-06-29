def read_input(filename):
    """
    Reads an array from the file filename.
    Returns a pair (n,array) where array is an array of size n*n
    """
    # Read the input file
    try:
        fp = open(filename)
        content = fp.read()
    except IOError:
        print "Error opening or reading input file: ", filename
        sys.exit()
    # Convert the input into words
    words = content.split()
    # Convert all words into integers
    try:
        numbers = map(int, words)
    except ValueError:
        print "Error: the input file doesn't consist of integers"
    # make sure the file is not empty
    if len(words) == 0:
        print "Error: the input file is empty"
        sys.exit()
    return numbers