import unittest


# merge two sorted array into one
def merge(array1, array2):
    ret = []
    i, j = 0, 0
    while i < len(array1) or j < len(array2):
        if j == len(array2) or \
                (i < len(array1) and array1[i] < array2[j]):
            ret.append(array1[i])
            i += 1
        else:
            ret.append(array2[j])
            j += 1
    return ret

# Given an array with list representation, merge sort on it
# and return the sorted array
def merge_sort(array):
    if array is None or len(array) <= 1:
        return array
    mid = len(array) // 2
    sorted_left = merge_sort(array[0:mid])
    sorted_right = merge_sort(array[mid:])
    merged = merge(sorted_left, sorted_right)
    return merged


class TestMergeSort(unittest.TestCase):
    def test_one(self):
        unordered = [3, 5, 6, 2, 4, 9, 11, 20, 1]
        res = merge_sort(unordered)
        prev = 0
        for val in res:
            self.assertTrue(prev < val)
            prev = val

    def test_two(self):
        unordered = [3, 5, 6, 2, 4, 9, 11, 20]
        res = merge_sort(unordered)
        prev = 0
        for val in res:
            self.assertTrue(prev < val)
            prev = val


if __name__ == '__main__':
    unittest.main()