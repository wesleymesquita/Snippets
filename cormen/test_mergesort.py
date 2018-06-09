import unittest
from random import randint, shuffle
from time import time

import mergesort



class TestMergeSort(unittest.TestCase):

    def test__merge(self):
        A = [6,7,8,9,0,1,2,3,5]
        mergesort._merge(A,0,len(A))
        self.assertEqual(A,[0,1,2,3,5,6,7,8,9])
    
        A = [4,3,2,10,6,1,8,7]
        mergesort._merge(A,0,len(A))
        self.assertEqual(A,[4,3,2,6,1,8,7,10])

        A = [1]
        mergesort._merge(A,0,len(A))
        self.assertEqual(A,[1])
        
        A = [1,2]
        mergesort._merge(A,0,len(A))
        self.assertEqual(A,[1,2])
    
        A = [2,1]
        mergesort._merge(A,0,len(A))
        self.assertEqual(A,[1,2])
   
    def test_merge_sort(self):
        t0 = time()
        self._do_test_merge_sort(merge_func=mergesort._merge)
        print("\nMergeSort with list took {:.6f} seconds".format(time()-t0))

    def test_merge_sort_deque(self):
        t0 = time()
        self._do_test_merge_sort(merge_func=mergesort._merge_deque)
        print("\nMergeSort with deque took {:.6f} seconds".format(time()-t0))

    def _do_test_merge_sort(self, merge_func):
        A = []
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, [])	

        A = [6]
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, [6])	
    
        A = [1,2]
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, [1,2])	

        A = [2,1]
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, [1,2])	

       
        A = [1,1]
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, [1,1])	
        
        A = [2,2,2,1]
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, [1,2,2,2])	
        
        A = ["2","2","2","1"]
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, ["1","2","2","2"])	
        
        NITEMS = 2**20 
        Expected = [randint(0, NITEMS) for i in range(NITEMS)]
        A = Expected.copy()
        Expected.sort()
        mergesort.merge_sort(A,0,len(A),merge_func)
        self.assertEqual(A, Expected)
   
if __name__ == '__main__':
    unittest.main(verbosity=2) 
