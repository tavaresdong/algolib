#!/usr/bin/python

# list slice nums[1:5] will contain 1, 2, 3, 4 indexed elements

class PeakElement(object):
    def findPeakElement(self, nums):
        if len(nums) == 1:
            return 0
        mid = len(nums) // 2
        if mid == 0:
            if nums[mid] > nums[mid + 1]:
                return mid
            else:
                return mid + 1 + self.findPeakElement(nums[mid + 1:])
        elif mid == len(nums) - 1:
            if nums[mid] > nums[mid - 1]:
                return mid
            else:
                return self.findPeakElement(nums[:mid])
        else:
            if nums[mid - 1] < nums[mid] and nums[mid + 1] < nums[mid]:
                return mid
            elif nums[mid - 1] < nums[mid]:
                return mid + 1 + self.findPeakElement(nums[mid + 1:])
            else:
                return self.findPeakElement(nums[:mid])


def main():
    nums = [1, 2, 3, 1]
    nums2 = [2, 1]
    nums3 = [1, 2, 3]
    pe = PeakElement()
    peak = pe.findPeakElement(nums3)
    print("Peak element is ", peak)


if __name__ == "__main__":
    main()