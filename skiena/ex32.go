package main

import (
	"fmt"
)

type Node struct {
	Val  int
	Next *Node
}

func createList(vals []int) (head *Node) {
	head = nil
	if len(vals) == 0 {
		return
	}
	tn := &Node{Val: vals[0], Next: nil}
	head = tn
	for _, v := range vals[1:] {
		tn.Next = &Node{Val: v, Next: nil}
		tn = tn.Next
	}
	return
}

func convToArray(head *Node) (a []int) {
	a = []int{}

	tn := head
	for {
		if tn == nil {
			break
		}
		a = append(a, tn.Val)
		tn = tn.Next
	}
	return
}

func reverseList(head *Node) (*Node, error) {
	if head == nil {
		return nil, fmt.Errorf("null list")
	}

	s := []*Node{}
	tn := head
	for {
		if tn == nil {
			break
		}
		s = append(s, tn)
		tn = tn.Next
	}

	i := len(s) - 1
	tn = s[i]

	for {
		if i < 0 {
			break
		}
		tn.Next = s[i]
		tn = tn.Next
		i--
	}
	tn.Next = nil
	return s[len(s)-1], nil
}

type testInstance struct {
	Input     []int
	ExpOutput []int
}

func runTests(tests []testInstance) (result bool) {
	result = true
	for _, t := range tests {
		l := createList(t.Input)
		rl, _ := reverseList(l)
		r := convToArray(rl)
		fmt.Printf("List : %d\n", r[0])
		for i, v := range t.ExpOutput {
			if v != r[i] {
				result = false
				fmt.Printf("Input %v . Expected %v. Got %v\n", t.Input, t.ExpOutput, r)
				break
			}
		}
		if result == false {
			break
		}
	}
	return
}

func main() {
	tests := []testInstance{
		{[]int{1, 2, 3}, []int{3, 2, 1}},
		{[]int{1}, []int{1}},
		{[]int{1, 2, 3, 4}, []int{4, 3, 2, 1}},
	}

	fmt.Printf("Test Result : %t\n", runTests(tests))
}
