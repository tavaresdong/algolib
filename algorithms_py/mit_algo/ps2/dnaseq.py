#!/usr/bin/env python2.7

import unittest
import sys
from mit_algo.ps2.dnaseqlib import *

### Utility classes ###

# Produces hash values for a rolling sequence.
class RollingHash:
    # Initializes a new rolling hash of the iterable sequence s.
    # (Remember that, in Python, this includes strings!)
    def __init__(self, s, BASE=37):
        self.BASE = BASE
        x = 0
        self.lst = list(s)
        for v in self.lst:
            x = (x * self.BASE) + hash(v)
        self.hash_val = x % sys.maxsize

    # Returns the current hash value.
    def hash(self):
        return self.hash_val

    # Updates the hash by removing previtm and adding nextitm.
    # This implements rolling hash
    # Returns the updated hash value.
    def slide(self, previtm, nextitm):
        self.hash_val -= (hash(previtm) * (self.BASE ** (len(self.lst) - 1)))
        self.hash_val *= self.BASE
        self.hash_val += hash(nextitm)
        self.hash_val %= sys.maxsize
        self.lst.pop(0)
        self.lst.append(nextitm)

# Maps integer keys to a set of arbitrary values.
class Multidict:
    # Initializes a new multi-value dictionary, and adds any key-value
    # 2-tuples in the iterable sequence pairs to the data structure.
    def __init__(self, pairs=[]):
        self.d = dict()
    # Associates the value v with the key k.
    def put(self, k, v):
        if k in self.d:
            self.d[k].append(v)
        else:
            self.d[k] = [v]
    # Gets any values that have been associated with the key k; or, if
    # none have been, returns an empty sequence.
    def get(self, k):
        if k in self.d:
            return self.d[k]
        else:
            return []



# Similar to subsequenceHashes(), but returns one k-length subsequence
# every m nucleotides.  (This will be useful when you try to use two
# whole data files.)
def intervalSubsequenceHashes(seq, k, m):
    b, e = 0, 0
    buffer = ''
    init = 0
    gap = m
    flag = False
    roll = None
    for v in seq:
        if flag is False:
            buffer += v
            e += 1
            if len(buffer) == k:
                flag = True
                roll = RollingHash(buffer, BASE=4)
                yield buffer, roll.hash(), b
        else:
            roll.slide(buffer[0], v)
            buffer = buffer[1:] + v
            b += 1
            gap -= 1
            if gap == 0:
                yield buffer, roll.hash(), b
                # print(buffer, " ", roll.hash())
                gap = m

# Searches for commonalities between sequences a and b by comparing
# subsequences of length k.  The sequences a and b should be iterators
# that return nucleotides.  The table is built by computing one hash
# every m nucleotides (for m >= k).
def getExactSubmatches(a, b, k, m):
    print ("Testing Exact Submatches")
    md = Multidict()
    for hash_a, key_a, pos_a in intervalSubsequenceHashes(a, k, m):
        md.put(hash_a, (key_a, pos_a))
    for hash_b, key_b, pos_b in intervalSubsequenceHashes(b, k, m):
        for ka, pa in md.get(hash_b):
            if key_b == ka:
                yield pa, pos_b


# Uncomment this when you're ready to generate comparison images.  The
# arguments are, in order: 1) Your getExactSubmatches function, 2) the
# filename to which the image should be written, 3) a tuple giving the
# width and height of the image, 4) the filename of sequence A, 5) the
# filename of sequence B, 6) k, the subsequence size, and 7) m, the
# sampling interval for sequence A.
#compareSequences(getExactSubmatches, 'maternal-paternal.png', (500,500), 'fmaternal.fa', 'fpaternal.fa', 20, 10000)

### Testing ###

class TestRollingHash(unittest.TestCase):
    def test_rolling(self):
        rh1 = RollingHash('abcde')
        rh2 = RollingHash('bcdef')
        rh3 = RollingHash('cdefZ')
        rh1.slide('a','f')
        self.assertTrue(rh1.hash() == rh2.hash())
        rh1.slide('b','Z')
        self.assertTrue(rh1.hash() == rh3.hash())
        #print("sys.maxsize:", sys.maxsize)


class TestMultidict(unittest.TestCase):
    def test_multi(self):
        foo = Multidict()
        foo.put(1, 'a')
        foo.put(2, 'b')
        foo.put(1, 'c')
        print("Testing Multidict")
        self.assertTrue(foo.get(1) == ['a','c'])
        self.assertTrue(foo.get(2) == ['b'])
        self.assertTrue(foo.get(3) == [])

# This test case may be useful before you add the argument m
class TestExactSubmatches(unittest.TestCase):
    def test_one(self):
        foo = 'yabcabcabcz'
        bar = 'xxabcxxxx'
        matches = list(getExactSubmatches(iter(foo), iter(bar), 3, 1))
        print (len(matches))
        correct = [(1,2), (4,2), (7,2)]
        self.assertTrue(len(matches) == len(correct))
        for x in correct:
            self.assertTrue(x in matches)



if __name__ == '__main__':
    #unittest.main()
    import os
    dirpath = os.path.abspath(os.path.dirname(sys.path[0]))

    # The arguments are, in order: 1) Your getExactSubmatches
    # function, 2) the filename to which the image should be written,
    # 3) a tuple giving the width and height of the image, 4) the
    # filename of sequence A, 5) the filename of sequence B, 6) k, the
    # subsequence size, and 7) m, the sampling interval for sequence
    # A.
    compareSequences(getExactSubmatches, dirpath + '\\output.png', \
                     (500,500), 'C:\\fmaternal.fa', 'C:\\fpaternal.fa', 8, 100)

