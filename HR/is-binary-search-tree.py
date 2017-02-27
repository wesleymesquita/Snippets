# Enter your code here. Read input from STDIN. Print output to STDOUT
""" Node is defined as
class node:
  def __init__(self, data):
      self.data = data
      self.left = None
      self.right = None
"""
def check_binary_search_tree_(root):
    nodes = set()
    nodes.add(root)
    return check_binary_search_tree(root, nodes)

#https://www.hackerrank.com/challenges/is-binary-search-tree
def check_binary_search_tree(root, nodes):
            
  
    if root == None:
        return True
    else:                        
        left_nodes = set()
        right_nodes = set()
     
        is_right_good = True                
        is_left_good = True
        
        if root.left != None:
            left_nodes.add(root.left)
            is_left_good = check_binary_search_tree(root.left, left_nodes)
            if len(left_nodes) > 0:            
                for n in left_nodes:
                    if n.data >= root.data:
                        is_left_good = False
                        break
                if is_left_good:
                    nodes.update(left_nodes)
        
        if root.right != None:
            right_nodes.add(root.right)
            is_right_good = check_binary_search_tree(root.right,right_nodes)
            if len(right_nodes) >0:
                for n in right_nodes:
                    if n.data <= root.data:
                        is_right_good = False
                        break
                if is_right_good:
                    nodes.update(right_nodes)
            
                
        return is_right_good and is_left_good  
  
