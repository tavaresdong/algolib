import unittest

class Solution(object):
    def merge(self, nums1, m, nums2, n):
        """
        :type nums1: List[int]
        :type m: int
        :type nums2: List[int]
        :type n: int
        :rtype: void Do not return anything, modify nums1 in-place instead.
        """
        pos = m + n - 1
        while pos >= 0:
            if m == 0:
                nums1[0:pos + 1] = nums2[0:n]
                break
            elif n == 0:
                break
            else:
                if nums1[m - 1] > nums2[n - 1]:
                    nums1[pos] = nums1[m - 1]
                    m -= 1
                else:
                    nums1[pos] = nums2[n - 1]
                    n -= 1
            pos -= 1


class TestMergeSort(unittest.TestCase):
    def test_one(self):
        nums1 = [3, 5, 6, 8, 9, 10, 15]
        nums2 = [4, 7, 11]
        sol = Solution()
        sol.merge(nums1, 4, nums2, 3)
        prev = 0
        for val in nums1:
            self.assertTrue(prev < val)
            prev = val
        self.assertTrue(nums1[0] == 3)
        self.assertTrue(nums1[6] == 11)

    def test_two(self):
        nums1 = [4, 5, 6, 0, 0, 0]
        nums2 = [1, 2, 3]
        sol = Solution()
        sol.merge(nums1, 3,  nums2, 3)
        prev = 0
        for val in nums1:
            self.assertTrue(prev < val)
            prev = val
        self.assertTrue(nums1[0] == 1)
        self.assertTrue(nums1[5] == 6)
        self.assertTrue(len(nums1) == 6)



if __name__ == '__main__':
    unittest.main()