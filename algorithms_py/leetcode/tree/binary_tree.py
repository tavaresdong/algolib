

class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution(object):

    def invertTree(self, root):
        '''
        Solution for problem "invert binary tree"
        :param root: TreeNode
        :return: root TreeNode  of inverted tree
        '''
        if root is None:
            return None
        orig_right = root.right
        root.right = self.invertTree(root.left)
        root.left = self.invertTree(orig_right)
        return root
