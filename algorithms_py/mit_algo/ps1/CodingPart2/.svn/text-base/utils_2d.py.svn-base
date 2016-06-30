def is_a_peak(n, matrix, (x, y)):
    """
    Checks if a given location (x,y) is a peak in an array of size n*n
    """
    value = matrix[x][y]
    if x > 0 and matrix[x-1][y] > value:
        return False
    if y > 0 and matrix[x][y-1] > value:
        return False
    if x < n - 1 and matrix[x+1][y] > value:
        return False
    if y < n - 1 and matrix[x][y+1] > value:
        return False
    return True

def count_peaks(n, matrix):
    """
    Counts the number of peaks in an array of size n*n
    """
    peaks = 0
    for x in range(0, n):
        for y in range(0, n):
           if is_a_peak(n, matrix, (x, y)):
              peaks += 1
    return peaks

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
    n = numbers[0]
    if len(numbers) != n*n + 1:
        print "Error: the file contains an incorrect number of integers"
        sys.exit()
    matrix = [[numbers[i + j*n + 1] for i in range(0, n)] for j in range(0, n)]
    peaks = count_peaks(n, matrix)
    print "Read file %s with n = %d and %d peaks" %(filename, n, peaks)
    # construct array
    return (n, matrix)