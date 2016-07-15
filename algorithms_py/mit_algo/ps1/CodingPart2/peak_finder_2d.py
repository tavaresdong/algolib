import sys

############### Auxiliary functions #####################
def find_column_global_max(matrix, x, y0, y1):
    """ Finds global maximum of column x between rows y0 and y1 (inclusive). """
    best_y = y0
    best_h = matrix[x][best_y]
    for y in range(y0+1, y1+1):
        h = matrix[x][y]
        if best_h < h:
            best_y = y
            best_h = h
    return (best_y, best_h)


def find_row_global_max(matrix, x0, x1, y):
    """ Finds global maximum of row y between columns x0 and x1 (inclusive). """
    best_x = x0
    best_h = matrix[best_x][y]
    for x in range(x0+1, x1+1):
        h = matrix[x][y]
        if best_h < h:
            best_x = x
            best_h = h
    return (best_x, best_h)


def find_global_max(matrix, x0, x1, y0, y1):
    """ Finds global maximum of sub-matrix between columns x0 and x1 and rows y0 and y1 (inclusive). """
    best_x = x0
    best_y = y0
    best_h = matrix[best_x][best_y]
    for x in range(x0, x1+1):
        for y in range(y0, y1+1):
            h = matrix[x][y]
            if(best_h < h):
                best_x = x
                best_y = y
                best_h = h
    return (best_x, best_y, best_h)


def is_peak(matrix, x, y, x0, x1, y0, y1):
    print("value:", matrix[x][y])
    if x > x0 and matrix[x - 1][y] > matrix[x][y]:
        print(matrix[x - 1][y], x - 1, y)
        return (x - 1, y, False)
    if x < x1 and matrix[x + 1][y] > matrix[x][y]:
        print(matrix[x + 1][y], x + 1, y)
        return (x + 1, y, False)
    if y > y0 and matrix[x][y - 1] > matrix[x][y]:
        print(matrix[x][y - 1], x, y - 1)
        return (x, y - 1, False)
    if y < y1 and matrix[x][y + 1] > matrix[x][y]:
        print(matrix[x][y + 1], x, y + 1)
        return (x, y + 1, False)
    return (x, y, True)

####################### Algorithms Implementation #########################

"""Find a peak of a mountain range.

The mountain range is a 2-dimensional matrix of integers values,
indexed by closed intervals [x0,x1] and [y0,y1].

A peak is defined as a location which is at least as high as the adjacent
locations (two locations are adjacent if they share a common edge).

Keyword arguments:
matrix -- a matrix of altitudes
x0 -- an integer which is the leftmost index of the range
x1 -- an integer which is the rightmost index of the range
y0 -- an integer which is the bottom-most index of the range
y1 -- an integer which is the topmost index of the range

Return value: a pair of coordinates (x, y) of any local maximum location

"""
def quick_find_2d_peak(matrix, x0, x1, y0, y1):
    """
    Implement O(n) solution given in lecture.
    """
    ########### WRITE YOUR IMPLEMENTATION HERE ############
    xmid = (x0 + x1) // 2
    ymid = (y0 + y1) // 2
    xpos, ypos, maxh = x0, y0, 0
    (xpos, maxh) = find_row_global_max(matrix, x0, x1, y0)

    (x, h) = find_row_global_max(matrix, x0, x1, ymid)
    if h > maxh:
        xpos, ypos, maxh = x, ymid, h

    (x, h)  = find_row_global_max(matrix, x0, x1, y1)
    if h > maxh:
        xpos, ypos, maxh = x, y1, h

    (y, h) = find_column_global_max(matrix, x0, y0, y1)
    if h > maxh:
        xpos, ypos, maxh = x0, y, h

    (y, h) = find_column_global_max(matrix, xmid, y0, y1)
    if h > maxh:
        xpos, ypos, maxh = xmid, y, h

    (y, h) = find_column_global_max(matrix, x1, y0, y1)
    if h > maxh:
        xpos, ypos, maxh = x1, y, h

    (larger_x, larger_y, peak) = is_peak(matrix, xpos, ypos, x0, x1, y0, y1)
    if peak is True:
        return (xpos, ypos)
    else:
        if larger_x < xmid:
            if larger_y < ymid:
                return quick_find_2d_peak(matrix, x0 + 1, xmid - 1, y0 + 1, ymid - 1)
            else:
                return quick_find_2d_peak(matrix, x0 + 1, xmid - 1, ymid + 1, y1 - 1)
        elif larger_x > xmid:
            if larger_y < ymid:
                return quick_find_2d_peak(matrix, xmid + 1, x1 - 1, y0 + 1, ymid - 1)
            else:
                return quick_find_2d_peak(matrix, xmid + 1, x1 - 1, ymid + 1, y1 - 1)


    #######################################################


def medium_find_2d_peak(matrix, x0, x1, y0, y1):
    """
    Implements O(n log(n)) solution given in lecture.
    """
    
    while x0 < x1: 

        mid_x = (x0+x1) // 2 # If the width of the range is even,
                          # this picks the cell slightly to the left of the middle
 
        mid_col_glob_max = find_column_global_max(matrix, mid_x, y0, y1)
        right_col_glob_max = find_column_global_max(matrix, mid_x + 1, y0, y1)

        if right_col_glob_max[1] > mid_col_glob_max[1]:
            x0 = mid_x + 1 # choose the right half
        else:
            x1 = mid_x # choose the left half
             
    max_y_and_value = find_column_global_max(matrix, x0, y0, y1)
    return (x0, max_y_and_value[0])


def slow_find_2d_peak(matrix, x0, x1, y0, y1):
    """
    Implements O(n^2) solution given in lecture.
    """
    result = find_global_max(matrix, x0, x1, y0, y1)
    return (result[0], result[1])
##########################################################################