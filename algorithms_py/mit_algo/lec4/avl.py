import mit_algo.lec3.bst


def height(node):
    if node is None:
        return -1
    else:
        return node.height


def size(node):
    if node is None:
        return 0
    else:
        return node.size


def update_node_info(node):
    node.height = max(height(node.left), height(node.right)) + 1
    node.size = size(node.left) + size(node.right) + 1

class AVL(mit_algo.lec3.bst.BST):

    def left_rotate(self, x):
        y = x.right
        y.parent = x.parent
        if y.parent is None:
            self.root = y
        else:
            if y.parent.left is x:
                y.parent.left = y
            elif y.parent.right is x:
                y.parent.right = y
        x.right = y.left
        if x.right is not None:
            x.right.parent = x
        y.left = x
        x.parent = y
        update_node_info(x)
        update_node_info(y)
        return y

    def right_rotate(self, x):
        y = x.left
        y.parent = x.parent
        if y.parent is None:
            self.root = y
        else:
            if y.parent.left is x:
                y.parent.left = y
            elif y.parent.right is x:
                y.parent.right = y
            x.left = y.right
            if x.left is not None:
                x.left.parent = x
            y.right = x
            x.parent = y
        update_node_info(x)
        update_node_info(y)
        return y

    def insert(self, t):
        node = mit_algo.lec3.bst.BST.insert(self, t)
        self.rebalance(node)

    def delete(self, t):
        print("AVL delete: ", t)
        node, parent = mit_algo.lec3.bst.BST.delete(self, t)
        if parent is not None:
            self.rebalance(parent)

    def size(self):
        if self.root is None:
            return 0
        else:
            return self.root.size

    def rebalance(self, node):
        """
        Rebalance the tree, from bottom to top
        """
        cur = node
        while cur is not None:
            update_node_info(cur)
            left_ht = height(cur.left)
            right_ht = height(cur.right)
            if left_ht - right_ht > 1:
                if height(node.left.left) >= height(node.left.right):
                    self.left_rotate(cur)
                else:
                    self.left_rotate(cur.left)
                    self.right_rotate(cur)
            elif right_ht - left_ht > 1:
                if height(cur.right.right) >= height(cur.right.left):
                    self.left_rotate(cur)
                else:
                    self.right_rotate(cur.right)
                    self.left_rotate(cur)

            cur = cur.parent

    def delete_min(self):
        node, parent = mit_algo.lec3.bst.BST.delete_min(self)
        self.rebalance(parent)


    def num_nodes_smaller_than(self, t):
        '''
        Return # of nodes with value smaller than t,
        in O(logn) time complexity
        :param t: the value to compare
        :return: num of nodes smaller than t
        '''
        count = 0
        node = self.root
        while node is not None:
            if node.key == t:
                return count + size(node.left)
            elif node.key < t:
                count = count + size(node.left) + 1
                node = node.right
            else:
                node = node.left
        return count

    def range(self, begin, end):
        '''
        return the values in this tree in between begin and end
        :param begin: the begin value
        :param end: the end value
        :return: a list of the value in [begin, end]
        '''
        return self.num_nodes_smaller_than(end + 1) \
                - self.num_nodes_smaller_than(begin)


def test(args=None):
    mit_algo.lec3.bst.test(args, BSTType=AVL)

if __name__ == '__main__': test()