class LinkedList(object):
	def __init__(self):
		pass
	def insert(self, val):
		pass
	def search(self, val):
		pass
	def delete(self, val):
		pass
	def successor(self, val):
		pass
	def __iter__(self): 
		pass
	def __next__(self):
		pass

class SingleLinkedList(LinkedList):
	def __init__(self):
		self._val = None
		self._next = None
		self._iter_node = self
		self._size = 0
	def insert(self, val):
		if self._val is None:
			self._val = val
			self._size = 1
		else:
			last_node = self
			while last_node._next is not None:
				last_node._size = last_node._size + 1
				last_node = last_node._next
			last_node._next = SingleLinkedList()
			last_node._next._val = val
			self._size = self._size + 1
			return last_node._next
	def search(self, val):
		for n in self:
			if n._val == val:
				return n
		return None 
	def delete(self, val):
		if self._val is None:
			return self
		if self._val == val:
			if self._next is None:
				self._val = None
				self._size = 0
			else:
				self._val = self._next._val
				self._next = self._next._next
				self._size = self._size - 1
			return self
		next_node = self._next
		curr_node = self
		while next_node is not None and next_node._val != val:
			curr_node = next_node
			next_node = curr_node._next	
		if next_node is not None:
			curr_node._next = next_node._next
			return curr_node
		return None	
	
	def _is_bigger(self, a, b, is_bigger=True):
		if is_bigger:
			return a>b
		return a<b
	def successor(self,val,is_successor=True):
		val_node = self.search(val)
		if val_node is None:
			return None
		candidate = None 
		for node in self:
			if candidate is None and self._is_bigger(node._val, val, is_successor):
				candidate = node._val
			elif candidate is not None and self._is_bigger(node._val, val, is_successor):
				if abs(node._val-val) < abs(candidate-val):
					candidate = node._val
		return candidate	
	def predecessor(self,val):
		return self.successor(val, is_successor=False)
	def __iter__(self): 
		self._iter_node = self
		return self
	def __next__(self):
		if self._iter_node is None:
			self.iter_node = self
			raise StopIteration
		next_item = self._iter_node
		self._iter_node = self._iter_node._next
		return next_item
	def __str__(self):
		"""
		String representation . Empty list is '()'.
		"""
		s = "("
		if self._val != None:
			s += str(self._val)
			if self._next is not None:
				for n in self._next:
					s = s + "".join(["->", str(n._val)])
		s = s + ")"
		return s	
	def __len__(self):
		""" Empty list has 0 (zero) nodes """
		return self._size
	
