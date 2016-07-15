#!/bin/python3

def find_min(node):
    cur = node
    if cur is None:
        return None
    else:
        while cur.left is not None:
            cur = cur.left
        return cur


def find_nd(root, t):
    node = root
    while node is not None:
        if node.key == t:
            return node
        elif node.key < t:
            node = node.right
        else:
            node = node.left
    return None


def successor(cur):
    """Find successor of node with value t

    :param t: the value to start
    :return:the node contianing value next-larger to t
    """
    if cur is not None:
        if cur.right is not None:
            return find_min(cur.right)
        else:
            while cur.parent is not None \
                    and cur.parent.right is cur:
                cur = cur.parent
            return cur.parent
    return None




class BST(object):
    def __init__(self):
        self.root = None

    def insert(self, t):
        """Insert key t into binary search tree BST,
           Modifying it in-place, do not insert duplicated keys
        """
        node = BSTNode(t)
        p = None
        cur = self.root
        while cur is not None and cur.key != t:
            p = cur
            if t > cur.key:
                cur = cur.right
            else:
                cur = cur.left
        if cur is None:
            if p is None:
                self.root = node
            else:
                if t < p.key:
                    p.left = node
                else:
                    p.right = node
                node.parent = p
        return node

    def find(self, t):
        node = self.root
        while node is not None:
            if node.key == t:
                return node
            elif node.key < t:
                node = node.right
            else:
                node = node.left
        return None



    def range(self, begin, end):
        '''
        return the values in this tree in between begin and end
        :param begin: the begin value
        :param end: the end value
        :return: a list of the value in [begin, end]
        '''
        node = self.root
        ret = 0
        while node.left is not None and node.key > begin:
            node = node.left
        while node is not None and node.key <= end:
            if node.key >= begin:
                ret += 1
            node = successor(node)
        return ret


    def delete(self, t):
        return self.delete_from_node(self.root, t)

    def delete_from_node(self, start, t):
        node = find_nd(start, t)
        if node is not None:
            if node.left is None and node.right is None:
                # Node has no children
                if node.parent is None:
                    self.root = None
                elif node.parent.left is node:
                    node.parent.left = None
                elif node.parent.right is node:
                    node.parent.right = None
                parent = node.parent
                node.disconnect()
                return node, parent
            elif node.left is None and node.right is not None:
                if node.parent is None:
                    self.root = node.right
                elif node.parent.left is node:
                    node.parent.left = node.right
                elif node.parent.right is node:
                    node.parent.right = node.right
                parent = node.parent
                node.disconnect()
                return node, parent
            elif node.right is None and node.left is not None:
                if node.parent is None:
                    self.root = node.left
                elif node.parent.left is node:
                    node.parent.left = node.left
                elif node.parent.right is node:
                    node.parent.right = node.left
                parent = node.parent
                node.disconnect()
                return node, parent
            else:
                succ = find_min(node.right)
                node.key = succ.key
                succ.key = t
                # After switched key, delete the successor directly(zero/one child case)
                return self.delete_from_node(succ, t)

    def size(self):
        return 0


    def delete_min(self):
        """Delete the minimum element
        Remove the smallest (left most)　element in the BST
        """
        if self.root is None:
            return None, None
        node = self.root
        while node.left is not None:
            node = node.left
        if node.parent is not None:
            node.parent.left = node.right
        else:
            self.root = node.right
        if node.right is not None:
            node.right.parent = node.parent
        parent = node.parent
        node.disconnect()
        return node, parent

    def __str__(self):
        if self.root is None:
            return '<empty tree>'
        def recurse(node):
            if node is None:
                return [], 0, 0
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
                     ' ' * left_pos + '/' + ' ' * (middle - 2) +
                     '\\' + ' ' * (right_width - right_pos)] + \
                    [left_line + ' ' * (width - left_width - right_width) +
                     right_line
                     for left_line, right_line in zip(left_lines, right_lines)]
            return lines, pos, width

        return '\n'.join(recurse(self.root)[0])


class BSTNode(object):
    def __init__(self, t):
        self.key = t
        self.disconnect()
        self.height = 0

    def disconnect(self):
        self.left = None
        self.right = None
        self.parent = None


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
    for item in items:
        tree.insert(item)
        print("size of the tree:", tree.size())
        print(tree)
    print("range between 3 and 20 has #", tree.range(3, 20))


if __name__ == '__main__':
    test()
