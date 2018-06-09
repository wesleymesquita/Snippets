"""Merge Sort algorithm implementation
See Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. 2009. 
Introduction to Algorithms, Third Edition (3rd ed.). The MIT Press. Pages 30-38
"""

def _merge(A, beg, end):
	if end-beg > 1: 
		mid = beg + (end-beg)//2
		L = A[beg:mid]
		L.append(None)
		R = A[mid:end]
		R.append(None)
		k,i,j = beg,0,0
		while k < end:
			if L[i] is None or R[j] is None:
				if L[i] is None: 
					A[k:(k+len(R[j:-1]))] = R[j:-1]
				elif R[j] is None:
					A[k:(k+len(L[i:-1]))] = L[i:-1]
				break
			if L[i]<R[j]:
				A[k] = L[i]
				i+=1
			else:
				A[k] = R[j]
				j+=1
			k+=1

def _merge_deque(A, beg, end):
	from collections import deque
	if end-beg > 1:
		mid = beg + (end-beg)//2
		L = deque(A[beg:mid])
		R = deque(A[mid:end])
		k = 0
		while len(L) > 0 or len(R) > 0:
			if len(L) == 0:
				A[k:] = list(R)
				R.clear()
				continue
			if len(R) == 0:
				A[k:] = list(L)
				L.clear()
				continue
			if L[0] <= R[0]:
				A[k] = L.popleft()	
			else:
				A[k] = R.popleft()
			k+=1
	
def merge_sort(A, beg, lsize, merge_func=_merge):
	"""
	merge sort algorithm implementation
	A is a list containing the elements
	beg = index of firt element
	lsize = size of vector starting from beg
	"""
	if  lsize-beg > 1:
		mid = beg + (lsize-beg)//2
		merge_sort(A, beg, mid)
		merge_sort(A, mid, lsize)
		merge_func(A, beg, lsize)
