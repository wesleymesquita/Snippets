from linked_list import SingleLinkedList
from collections import namedtuple
from random import randint, shuffle 

class test_SingleLinkedList():
    """
    Provide tests for SingleLinkedList class
    """
    def __init__(self):
        self.Test = namedtuple('Test', ['input', 'output'])
    def _T(self, testData):
        tests = []
        for td in testData:
            tests.append(self.Test(*td))
        return tests 

    def _create_obj(self,all_nodes):
        sl = SingleLinkedList()
        for node in all_nodes:
            sl.insert(node)
        return sl   

    def _eval_test(self, test, result):
        if result != test.output:
            print("Test Failed:\n\tInput:\t{}\n\tExpected: {}\n\tResult:\t{}".format(test.input,test.output,result))
        else:
            print("Test Passed:\n\tInput:\t{}".format(test.input))
        
    def test_insertion(self):
        print("\n** INSERTION **")
        tests = self._T([
                ([1], "(1)"), 
                ([1,2],"(1->2)"), 
                ([1,2,3],"(1->2->3)"),
                ([20,10,30,35,25,6,15], "(20->10->30->35->25->6->15)")
                ])
        for test in tests:
            obj = self._create_obj(test.input)
            self._eval_test(test, str(obj))

    def test_search(self):
        print("\n** SEARCH **")
        tests = self._T([
                ([1,1], True), 
                ([2,1,2],True), 
                ([3,1,2],False),
                ([1,1,2,3],True)
                ])
        for test in tests:
            obj = self._create_obj(test.input[1:])
            self._eval_test(test, obj.search(test.input[0]) is not None)
            
                
    def test_delete(self):
        print("\n** DELETE **")
        tests = self._T([
                ([1,1],"()"), 
                ([2,1,2],"(1)"), 
                ([1,1,2],"(2)"), 
                ([3,1,2], "(1->2)"),
                ([1,1,2,3], "(2->3)"),
                ([2,1,2,3], "(1->3)"),
                ([10,20,10,30,35,25,6,15], "(20->30->35->25->6->15)"),
                ([20,20,30,35,25,6,15], "(30->35->25->6->15)"),
                ([15,30,35,25,6,15], "(30->35->25->6)"),
                ])
        for test in tests:
            obj = self._create_obj(test.input[1:])
            obj.delete(test.input[0])
            self._eval_test(test, str(obj))
    def test_successor(self):
         
        print("\n** SUCCESSOR **")
        tests = self._T([
                ([1,1], "None"), 
                ([1,1,2],"2"), 
                ([2,1,2],"None"), 
                ([1,1,2,3], "2"),
                ([2,1,2,3], "3"),
                ([3,1,2,3], "None"),
                ([10,20,10,30,35,25,6,15], "15"),
                ([20,20,30,35,25,6,15], "25"),
                ([15,30,35,25,6,15], "25"),
                ])
        for test in tests:
            obj = self._create_obj(test.input[1:])
            result = obj.successor(val=test.input[0])
            self._eval_test(test, str(result))
                
    def test_predecessor(self):
         
        print("\n** PREDECESSOR  **")
        tests = self._T([
                ([1,1], "None"), 
                ([1,1,2],"None"), 
                ([2,1,2],"1"), 
                ([1,1,2,3], "None"),
                ([2,1,2,3], "1"),
                ([3,1,2,3], "2"),
                ([10,20,10,30,35,25,6,15], "6"),
                ([20,20,30,35,25,6,15], "15"),
                ([15,30,35,25,6,15], "6"),
                ])
        for test in tests:
            obj = self._create_obj(test.input[1:])
            result = obj.predecessor(val=test.input[0])
            self._eval_test(test, str(result))
    def test_free_tests(self, n_nodes):
        print("\n ** FREE TESTS **") 
        """Actions: add, search and remove  N (define below) items 
           Expected result: Find all items and have empty list "()" """
        N = n_nodes 
        obj = SingleLinkedList()

        obj_dataset = set()
        while len(obj_dataset) < N:
           obj_dataset.add(randint(0,N)) # this approach is not good, but works for simple case.
        obj_data = [e for e in obj_dataset] 
        print("TEST DATA : Input {}".format(obj_data))
        shuffle(obj_data)
        for d in obj_data:
            obj.insert(d)
            #print("After inserting {}, we got {}".format(d, obj))
        print("Resulted {}: {}".format(type(obj), obj))
        shuffle(obj_data)
        for d in obj_data:
            temp_obj = obj.search(d)
            if temp_obj is None:
                print("FAILED to find existing item {}".format(d)) 
          
        obj_data = sorted(obj_data)
        for i in range(0, len(obj_data)-1):
            temp_obj = obj.successor(obj_data[i])
            if temp_obj != obj_data[i+1]:
                print("FAILED to find sucessor item {}".format(d)) 
               
        obj_data = sorted(obj_data, reverse=True)
        for i in range(0, len(obj_data)-1):
            temp_obj = obj.predecessor(obj_data[i])
            if temp_obj != obj_data[i+1]:
                print("FAILED to find predecessor item {}".format(d)) 
    
        shuffle(obj_data)
        for d in obj_data:
            result = obj.delete(d)
            #print("After deleting {}, we got {}".format(d, obj))
            if result is None:
                print("FAILED : could not delete {}.".format(d))
        if str(obj) != "()":
            print("FAILED : obj is not empty after deleting all nodes. Got {}".format(obj))
        elif len(obj) != 0:
            print("FAILED : obj is not empty after deleting all nodes. Tree is has {} nodes".format(len(obj)))
        else:
            print("INSERTED, SEARCHED, SUCCESSOR, PREDECESSOR, DELETED {} items.".format(N)) 
    def run_tests(self):
        t.test_insertion()
        t.test_search() 
        t.test_delete()
        t.test_successor()
        t.test_predecessor()
        t.test_free_tests(n_nodes=2**12)
if __name__ == '__main__':
    t = test_SingleLinkedList()
    t.run_tests() 
