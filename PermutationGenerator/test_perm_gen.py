import unittest
import perm_gen

class TestPermGen(unittest.TestCase):
    def test_permutation_gen(self):
        source_str = 'a'
        result = perm_gen.permutations_gen(source_str) 
        self.assertEqual(result, ['a'])
        
        source_str = 'ab'
        result = perm_gen.permutations_gen(source_str) 
        self.assertEqual(result, ['ab', 'ba'])
    
        source_str = 'abc'
        result = perm_gen.permutations_gen(source_str) 
        self.assertEqual(result, ['abc', 'acb','bac','bca','cab','cba'])
        
