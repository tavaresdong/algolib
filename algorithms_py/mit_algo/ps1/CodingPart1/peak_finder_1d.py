def quick_find_1d_peak(array):
    """Finds a peak of a mountain range.

    The mountain range is a 1-dimensional array of values. A peak is
    defined as a location which is at least as high as the adjacent
    locations. Returns the index in the array of some peak.

    Keyword arguments:
    array -- an array containing the values

    returns the location x0 of the peak

    """

    ############## IMPLEMENT the O(log n) time algorithm here ############
    if len(array) == 1:
        return 0
    mid = len(array) // 2
    if mid == 0:
        if array[mid] > array[mid + 1]:
            return mid
        else:
            return mid + 1 + quick_find_1d_peak(array[mid + 1:])
    elif mid == len(array) - 1:
        if array[mid] > array[mid - 1]:
            return mid
        else:
            return quick_find_1d_peak(array[:mid])
    else:
        if array[mid - 1] < array[mid] and array[mid + 1] < array[mid]:
            return mid
        elif array[mid - 1] < array[mid]:
            return mid + 1 + quick_find_1d_peak(array[mid + 1:])
        else:
            return quick_find_1d_peak(array[:mid])

    ##################################################################


def slow_find_1d_peak(array):
    best_x = 0
    best_h = array[0]
    for x in range(1, len(array)):
        h = array[x]
        if best_h < h:
            best_x = x
            best_h = h
    return best_x