#!/usr/bin/python

class BSTNode(object):

    def __init__(self, parent, t):
        self.key = t
        self.parent = parent
        self.left = None
        self.right = None
        self.size = 1


    def update_stats(self):
        self.size = (0 if self.left is None else self.left.size) + \
                    (0 if self.right is None else self.right.size) + 1

    def insert(self, t, NodeType):
        self.size += 1
        if t < self.key:
            if self.left is None:
                self.left = NodeType(self, t)
                return self.left
            else:
                return self.left.insert(t, NodeType)
        else:
            if self.right is None:
                self.right = NodeType(self, t)
                return self.left
            else:
                return self.right.insert(t, NodeType)

    def find(self, t):
        if t == self.key:
            return self
        elif t < self.key:
            if self.left is None:
                return None
            else:
                return self.left.find(t)
        else:
            if self.right is None:
                return None
            else:
                return self.right.find(t)

    def rank(self, t):
        left_size = 0 if self.left is None else self.left.size
        if t == self.key:
            return left_size + 1
        elif t < self.key:
            if self.left is None:
                return 0
            else:
                return self.left.rank(self, t)
        else:
            if self.right is None:
                return left_size + 1
            else:
                return self.right.rank(t) + left_size + 1

    def minimum(self):
        node = self
        while node.left is not None:
            node = node.left
        return node

    # Take a close look at how successor is implemented
    def successor(self):
        if self.right is not None:
            return self.right.minimum()
        cur = self
        while cur is not None and cur.parent.right is cur:
            cur = cur.parent
        return cur.parent

    def delete(self):
        """
        Delete this node from the tree
        """
        if self.parent is None:
            pass
        elif self.left is None or self.right is None:
            if self.parent.left is self:
                self.parent.left = self.left or self.right
                if self.parent.left is not None:
                    self.parent.left.parent = self.parent
            else:
                self.parent.right = self.left or self.right
                if self.parent.right is not None:
                    self.parent.right.parent = self.parent
            cur = self.parent
            while cur.key is not None:
                cur.update_stats()
                cur = cur.parent
            return self
        else:
            s = self.successor()
            self.key, s.key = s.key, self.key
            return s.delete()

    def check(self, lokey, hikey):
        """Checks that the subtree rooted at t is a valid BST and all keys are between (lokey, hikey)."""
        if lokey is not None and self.key <= lokey:
            raise "BST RI violation"
        if hikey is not None and self.key >= hikey:
            raise "BST RI violation"
        if self.left is not None:
            if self.left.parent is not self:
                raise "BST RI violation"
            self.left.check(lokey, self.key)
        if self.right is not None:
            if self.right.parent is not self:
                raise "BST RI violation"
            self.right.check(self.key, hikey)
        if self.size != 1 + (0 if self.left is None else self.left.size) + (
                0 if self.right is None else self.right.size):
            raise "BST RI violation"

    def __repr__(self):
        return "<BST Node, key:" + str(self.key) + ">"

class BST(object):

    def __init__(self, NodeType=BSTNode):
        self.root = None
        self.NodeType = NodeType
        self.psroot = self.NodeType(None, None)

    def reroot(self):
        self.root = self.psroot.left

    def insert(self, t):
        if self.root is None:
            self.psroot.left = self.NodeType(self.psroot, t)
            self.reroot()
            return self.root
        else:
            self.root.insert(t, self.NodeType)

    def find(self, t):
        if self.root is None:
            return None
        else:
            return self.root.find(t)

    def rank(self, t):
        if self.root is None:
            return 0
        else:
            return self.root.rank(t)

    def delete(self, t):
        node = self.find(t)
        deleted = node.delete()
        self.reroot()
        return deleted

    def check(self):
        if self.root is not None:
            self.root.check(None, None)

    def __str__(self):
        if self.root is None: return '<empty tree>'
        def recurse(node):
            if node is None: return [], 0, 0
            label = str(node.key)
            left_lines, left_pos, left_width = recurse(node.left)
            right_lines, right_pos, right_width = recurse(node.right)
            middle = max(right_pos + left_width - left_pos + 1, len(label), 2)
            pos = left_pos + middle // 2
            width = left_pos + middle + right_width - right_pos
            while len(left_lines) < len(right_lines):
                left_lines.append(' ' * left_width)
            while len(right_lines) < len(left_lines):
                right_lines.append(' ' * right_width)
            if (middle - len(label)) % 2 == 1 and node.parent is not None and \
               node is node.parent.left and len(label) < middle:
                label += '.'
            label = label.center(middle, '.')
            if label[0] == '.': label = ' ' + label[1:]
            if label[-1] == '.': label = label[:-1] + ' '
            lines = [' ' * left_pos + label + ' ' * (right_width - right_pos),
                     ' ' * left_pos + '/' + ' ' * (middle-2) +
                     '\\' + ' ' * (right_width - right_pos)] + \
              [left_line + ' ' * (width - left_width - right_width) +
               right_line
               for left_line, right_line in zip(left_lines, right_lines)]
            return lines, pos, width
        return '\n'.join(recurse(self.root) [0])

test1 = range(0, 100, 10)
test2 = [31, 41, 59, 26, 53, 58, 97, 93, 23]
test3 = "algorithms"


def printsizes(node):
    if node is None:
        print ("node is nil")
    else:
        print ("node", node.key, "has a subtree of size", node.size)


def test(args=None, BSTtype=BST):
    import random, sys
    if not args:
        args = sys.argv[1:]
    if not args:
        print ('usage: %s <number-of-random-items | item item item ...>' % \
              sys.argv[0])
        sys.exit()
    elif len(args) == 1:
        items = (random.randrange(100) for i in range(int(args[0])))
    else:
        items = [int(i) for i in args]

    tree = BSTtype()
    print(tree)
    for item in items:
        tree.insert(item)
        print()
        print (tree)
    tree.delete(5)
    print()
    print(tree)
    print()
    print(tree.rank(3))


if __name__ == '__main__': test()