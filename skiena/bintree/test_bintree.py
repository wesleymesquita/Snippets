from bintree import BinTree
from collections import namedtuple
from random import randint, shuffle 

class test_BinTree():
    """
    Provide tests for BinTree class
    """
    def __init__(self):
        self.Test = namedtuple('Test', ['input', 'output'])
    def _T(self, testData):
        tests = []
        for td in testData:
            tests.append(self.Test(*td))
        return tests 
    
    def _create_BinTree(self, allNodes):
        bt = BinTree()
        for node in allNodes:
            bt.insert(node)
        return bt     

    def _eval_test(self, test, result):
        if result != test.output:
            print("Test Failed:\n\tInput:\t{}\n\tExpected:\t{}\n\tResult:\t{}".format(test.input,test.output,result))
        else:
            print("Test Passed:\n\tInput:\t{}".format(test.input))
        
    def test_insertion(self):
        print("\n** INSERTION **")
        tests = self._T([
                ([1], "(1)"), 
                ([1,2],"(1(2))"), 
                ([1,2,3],"(1(2(3)))"),
                ([20,10,30,35,25,6,15], "(((6)10(15))20((25)30(35)))")
                ])
        for test in tests:
            bt = self._create_BinTree(test.input)
            self._eval_test(test, str(bt))

    def test_search(self):
        print("\n** SEARCH **")
        tests = self._T([
                ([1,1], True), 
                ([2,1,2],True), 
                ([3,1,2],False),
                ([1,1,2,3],True)
                ])
        for test in tests:
            bt = self._create_BinTree(test.input[1:])
            self._eval_test(test, bt.search(test.input[0]) is not None)
            
                
    def test_delete(self):
        print("\n** DELETE **")
        tests = self._T([
                ([1,1],"()"), 
                ([2,1,2],"(1)"), 
                ([1,1,2],"(2)"), 
                ([3,1,2], "(1(2))"),
                ([1,1,2,3], "(2(3))"),
                ([2,1,2,3], "(1(3))"),
                ([10,20,10,30,35,25,6,15], "(((6)15)20((25)30(35)))"),
                ([20,20,30,35,25,6,15], "((6(15))25(30(35)))"),
                ([35,30,35,25,6,15], "(((6(15))25)30)"),
                ])
        for test in tests:
            bt = self._create_BinTree(test.input[1:])
            bt.delete(test.input[0])
            self._eval_test(test, str(bt))
        
    def test_free_tests(self):
        print("\n ** FREE TESTS **") 
        """Actions: add, search and remove  N (define below) items 
           Expected result: Find all items and have empty tree "()" """
    
        bt = BinTree()
        N = 2**10

        btDataSet = set()
        while len(btDataSet) < N:
           btDataSet.add(randint(0,N)) # this approach is horrible...
        btData = [e for e in btDataSet] 
        #print("TEST DATA : Input {}".format(btData))
        shuffle(btData)
        for d in btData:
            bt.insert(d)
            #print("After inserting {}, we got {}".format(d, bt))
        #print("Resulted Tree : {}".format(bt))
        shuffle(btData)
        for d in btData:
            tempBt = bt.search(d)
            if not tempBt:
                print("FAILED to find existing item {}".format(d)) 
        shuffle(btData)
        for d in btData:
            result = bt.delete(d)
            #print("After deleting {}, we got {}".format(d, bt))
            if not result:
                print("FAILED : could not delete {}.".format(d))
        if str(bt) != "()":
            print("FAILED : tree is not empty after deleting all nodes. Got {}".format(bt))
        elif len(bt) != 0:
            print("FAILED : tree is not empty after deleting all nodes. Tree is has {} nodes".format(len(bt)))
        else:
            print("INSERTED, SEARCHED and DELETED {} items.".format(N)) 
    def run_tests(self):
        t.test_insertion()
        t.test_search() 
        t.test_delete()
        t.test_free_tests()

if __name__ == '__main__':
    t = test_BinTree()
    t.run_tests() 
