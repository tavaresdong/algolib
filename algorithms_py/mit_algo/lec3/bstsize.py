#!/bin/python3

import mit_algo.lec3.bst


def size(node):
    if node is None:
        return 0
    else:
        return node.size


def update_size(node):
    node.size = size(node.left) + size(node.right) + 1


class BST(mit_algo.lec3.bst.BST):

    def __init__(self):
        self.root = None

    def insert(self, t):
        node = mit_algo.lec3.bst.BST.insert(self, t)
        while node is not None:
            update_size(node)
            node = node.parent

    def delete_min(self):
        deleted, parent = mit_algo.lec3.bst.BST.delete_min(self)
        node = parent
        while node is not None:
            update_size(node)
            node = node.parent


def test(args=None, BSTType=BST):
    import random, sys
    if not args:
        args = sys.argv[1:]
    if not args:
        print ("usage: %s <number-of-random-items | item item item ...>" % \
               sys.argv[0])
        sys.exit()
    elif len(args) == 1:
        items = (random.randrange(100) for i in range(int(args[0])))
    else:
        items = [int(i) for i in args]

    tree = BSTType()
    print(tree)
    print("current tree size :", size(tree.root))
    for item in items:
        tree.insert(item)
        print()
        print("current tree size :", size(tree.root))
        print(tree)

if __name__ == '__main__':
    test()

