"""Merge Sort algorithm implementation
See Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. 2009. 
Introduction to Algorithms, Third Edition (3rd ed.). The MIT Press. Pages 30-38
"""
def merge_sort(A, beg, end):
	if  end-beg > 1:
		mid = beg + (end-beg)//2
		merge_sort(A, beg, mid)
		merge_sort(A, mid, end)
		_merge(A, beg, end)
	
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
