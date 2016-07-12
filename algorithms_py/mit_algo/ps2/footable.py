from array import array

# An alternative to Python's dict class.
class Footable:
    # Creates a new hashtable.
    def __init__(self):
        self.tablesize = 32
        self.data = [None] * self.tablesize
        return
    # Inserts v into the hashtable with the key k.  Raises KeyError if
    # the key k already has a value associated with it.
    def put(self, k, v):
        assert int == type(k) and k >= 0
        if None != self.data[k % self.tablesize]:
            raise KeyError
        self.data[k % self.tablesize] = v
        return
    # Removes the element with key k if it exists; raises KeyError if
    # it does not.
    def remove(self, k):
        assert int == type(k) and k >= 0
        if None == self.data[k % self.tablesize]:
            raise KeyError
        self.data[k % self.tablesize] = None
        return
    # Returns the element with key k if it exists; raises KeyError if
    # it does not.
    def get(self, k):
        assert int == type(k) and k >= 0
        val = self.data[k % self.tablesize]
        if None == val:
            raise KeyError
        return val

class FootableLinear(Footable):

    # Use linear probing to find a spot for our value
    def put(self, k, v):
        assert int == type(k) and k >= 0
        probe_round = 0
        while None != self.data[k + probe_round % self.tablesize] \
                and probe_round < self.tablesize:
            probe_round += 1
        if probe_round != self.tablesize:
            self.data[k % self.tablesize] = v
        return