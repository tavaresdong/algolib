#!/usr/bin/python
import unittest
from mit_algo.ps3.ps3b import *
from mit_algo.ps3.utils import *

# Checks correctness of algorithm
def isCorrect(filename):
    penalties = read_list("ps3b-sampledata/" + filename + ".in")
    correct_answer = read_integer("ps3b-sampledata/" + filename + ".out")
    answer = best_score(penalties)
    print("answer:", answer, " solution: ", correct_answer)
    return (answer == correct_answer)

# Testing framework for part B of problem set 3
class TestPS3PartB(unittest.TestCase):

    def setUp(self):
        pass

    def testHeapSort(self):
        lst = heap_sort([5,1,4,0])
        print(lst)
        self.assertTrue(heap_sort([5,1,4,0]) == [5,4,1,0])

    def test1(self):
        doesPass = isCorrect("ps3b-sample0")
        self.assertTrue(doesPass)

    def test2(self):
        doesPass = isCorrect("ps3b-sample1")
        self.assertTrue(doesPass)

    def test3(self):
        doesPass = isCorrect("ps3b-sample2")
        self.assertTrue(doesPass)

    def test4(self):
        doesPass = isCorrect("ps3b-sample3")
        self.assertTrue(doesPass)

    def test5(self):
        doesPass = isCorrect("ps3b-sample4")
        self.assertTrue(doesPass)

    def test6(self):
        doesPass = isCorrect("ps3b-sample5")
        self.assertTrue(doesPass)

    def test7(self):
        doesPass = isCorrect("ps3b-sample6")
        self.assertTrue(doesPass)

    def test8(self):
        doesPass = isCorrect("ps3b-sample7")
        self.assertTrue(doesPass)

    def test9(self):
        doesPass = isCorrect("ps3b-sample8")
        self.assertTrue(doesPass)

    def test10(self):
        doesPass = isCorrect("ps3b-sample9")
        self.assertTrue(doesPass)

    def test11(self):
        doesPass = isCorrect("ps3b-sample10")
        self.assertTrue(doesPass)

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestPS3PartB)
    unittest.TextTestRunner(verbosity=2).run(suite)
