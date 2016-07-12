#!/usr/bin/env python

import sys

# Arguments: fn is the function to be evaluated; size is the size of
# the keyspace; vals is the set of values to use for evaluation.
# Returns a tuple: 0) load factor (proportion of values stored to
# number of slots) 1) proportion of nonempty slots 2) number of values
# that collide with another value 3) mean size of nonempty slot (as a
# float) 4) median size of nonempty slot (as a float) 5) size of
# largest slot
def hashEval(fn, size, vals):
  print("vals are:")
  for val in vals:
      print(val)
  d = {}
  load_factor = len(vals) / size
  collides = 0
  non_empty = 0
  for val in vals:
    key = fn(val) % size
    if key in d:
      d[key].append(val)
      collides += 1
    else:
      d[key] = [val]
      non_empty += 1
  slotlens = []
  for k, v in d.items():
    slotlens.append(len(v))
  sortedslotlens = sorted(slotlens)
  if len(sortedslotlens) % 2 == 0:
    mid = len(sortedslotlens) // 2
    median_size = (sortedslotlens[mid] + sortedslotlens[mid - 1]) / 2
  else:
    mid = len(sortedslotlens) // 2
    median_size = sortedslotlens[mid]
  ret = (load_factor, non_empty / size, collides,\
         len(vals) / non_empty, median_size,sortedslotlens[len(sortedslotlens) - 1])
  return ret


# Returns an iterable collection of qty random ints less than size.
# The ints should be uniformly distributed.
def randInts(size, qty):
  from random import randint
  vals = []
  for i in range(0, qty):
    vals.append(randint(0, size - 1))
  return vals


# Who says we aren't nice to you?  A simple helper function that
# pretty-prints the results of hashEval().
def printHashEval(fn, size, vals):
  result = hashEval(fn, size, vals)
  print ("Load factor:\t\t" + str(result[0]))
  print ("Proportion nonempty:\t" + str(result[1]))
  print ("Collisions:\t\t" + str(result[2]))
  print ("Mean size:\t\t" + str(result[3]))
  print ("Median size:\t\t" + str(result[4]))
  print ("Max size:\t\t" + str(result[5]))

# Takes a list of ints x representing a set and returns an integer
# hash.
def setHash(vals):
  BASE = 37
  x = 0
  # The keys should be unordered, so same set will result in same
  # hash value
  for v in sorted(vals):
    x = (x * BASE) + v
  return x % sys.maxsize

printHashEval(lambda x: x, 16, randInts(16, 8))
