"""
Binary Tree implementations
--------------------------

Binary tree class must implement methods:

- insert
- search
- successor (__next__)
- predecessor (__next__ on reversed)
- delete (__del__)
- string representatino (__str__)
"""
class BinTree(object):
	"""
	Implements basic binary tree with no balancing algorithm.
	By definition, the only assumption of this implementation is:
	Values in Left subtree are strictly lower (<) than the value in root
	and values in Right subtree are strictly higher (>).
	"""
	def __init__(self):
		"""
		The tree is initilized without nodes
		Any subsequent node need to be added using insert method
		"""
		self._val = None
		self._parent = None
		self._right = None
		self._left = None
		self._nnodes = 0
	def insert(self, val):
		"""
		Insert new value (val) in tree
		Return True if could insert, False otherwise
		TODO (wesleymesquita@gmail.com) : maybe makes more sense to return the subtree
										  where new val was inserted
		"""
		if self._val == val:
			return False
		
		if self._val is None:
			self._val = val
		elif val > self._val:
			if self._right is None:
				self._right = BinTree()
				self._right._val = val
				self._right._parent = self
				self._right._nnodes = 1
			else:
				return self._right.insert(val)
		else:
			if self._left is None:
				self._left = BinTree()
				self._left._val = val
				self._left._parent = self
				self._left._nnodes = 1
			else:
				return self._left.insert(val)
		self._nnodes = self._nnodes + 1
		return True

	def search(self, val):
		"""
		Search for val in tree
		Return subtree root containing val, None otherwise
		"""
		if val == self._val:
			return self
		elif val > self._val and self._right is not None:
			return self._right.search(val)
		elif val < self._val and self._left is not None:
			return self._left.search(val)
		else:
			return None

	def delete(self, val):
		"""
		Deletes val in tree
		Return True if could sucessfully delete node, False otherwise
		Note: The function will fail if value (val) could not be found
		"""
		result = self.search(val)
		if result is None:
			return False
		if result._right is None and result._left is None:
			if result._parent is not None and result == result._parent._right:
				result._parent._right = None
				result._parent._nnodes = result._parent._nnodes - 1 
			elif result._parent is not None and result == result._parent._left:
				result._parent._left = None
				result._parent._nnodes = result._parent._nnodes - 1 
			else:
				self._val = None
				self._nnodes = 0
		elif result._right is not None and result._left is None:
			if result._parent is not None:
				if result == result._parent._right:
					result._parent._right = result._right
				else:
					result._parent._left = result._right
				result._right._parent = result._parent
			else:
				curr = result._right
				while curr:
					if curr._left is None:
						break
					curr = curr._left
				curr._val, result._val = result._val, curr._val
				curr.delete(val)
		elif result._right is None and result._left is not None:
			if result._parent is not None:
				if result == result._parent._right:
					result._parent._right = result._left
				else:
					result._parent._left = result._left
				result._left._parent = result._parent
			else:
				curr = result._left
				while curr:
					if curr._right is None:
						break
					curr = curr._right
				curr._val, result._val = result._val, curr._val
				curr.delete(val)
		else:
			curr = result._right
			while True:
				if curr._left is None:
					break
				curr = curr._left
			curr._val, result._val = result._val, curr._val
			curr.delete(val)
		
		return True
	
	def __len__(self):
		"""
		Returns the amount of nodes in the three
		"""
		return self._nnodes
	def __str__(self):
		"""
		Returns a in-order traversal of tree.
		'()' represents empty tree
		Note : only empty tree has parenteses around empty
			   this is inconsistent and must be fixed
		"""
		text = '('
		if self._left is not None:
			text = text + str(self._left)
		if self._val is not None:
			text = text + str(self._val)
		if self._right is not None:
			text = text + str(self._right)
		text = text + ')'
		return text
