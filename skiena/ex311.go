package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Node struct {
	l, r   *Node
	val    int
	br, er int
}

func buildTree(numbers []int, br, er int) *Node {
	if br > er {
		return nil
	}
	if br == er {
		return &Node{val: numbers[br], br: br, er: er}
	}
	min := numbers[br]
	for i := br + 1; i <= er; i++ {
		if numbers[i] < min {
			min = numbers[i]
		}
	}
	r := &Node{val: min, br: br, er: er}
	r.l = buildTree(numbers, br, (br+er)/2)
	r.r = buildTree(numbers, ((br+er)/2)+1, er)
	return r
}

func BFS(root *Node, q *[]*Node) {
	if root != nil {
		*q = append(*q, root)
		BFS(root.l, q)
		BFS(root.r, q)
	}
}

func printTree(root *Node) {
	q := make([]*Node, 0)
	BFS(root, &q)
	for _, v := range q {
		fmt.Printf("[%d [%d-%d]] \n", v.val, v.br, v.er)
	}
}

func findMinimum(root *Node, br, er int) int {

	if root == nil {
		fmt.Printf("error! root == nil. Looking for [%d %d]\n", br, er)
		return 1 << 31
	}
	fmt.Printf("Looking for [%d - %d] | on curr node : [%d %d]\n", br, er, root.br, root.er)
	if root.br == br && root.er == er {
		return root.val
	}
	m := (root.br + root.er) / 2
	if br > m {
		return findMinimum(root.r, br, er)
	}
	if er < m {
		return findMinimum(root.l, br, er)
	}
	if er >= m && br <= m {
		min := 1 << 31
		lmin := 1 << 31
		rmin := 1 << 31

		fmt.Printf("root: [%d %d]. Begin : %d, End %d, m : %d\n", root.br, root.er, br, er, m)
		if m >= br {
			lmin = findMinimum(root.l, br, m)
		}
		if m < er {
			rmin = findMinimum(root.r, m+1, er)
		}
		if lmin < min {
			min = lmin
		}
		if rmin < min {
			min = rmin
		}
		return min
	}
	return 1 << 31
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	text, err := reader.ReadString('\n')
	if err != nil {
		log.Fatalf("Ooops... could not read text %v\n", err)
	}
	text = text[0 : len(text)-1]
	numbers := make([]int, 0)
	for _, v := range strings.Split(text, " ") {
		n, _ := strconv.Atoi(v)
		numbers = append(numbers, n)
	}

	root := buildTree(numbers, 0, len(numbers)-1)
	printTree(root)
	text, _ = reader.ReadString('\n')
	text = text[:len(text)-1]
	fmt.Printf("text == %s\n", text)
	i, _ := strconv.Atoi(strings.Split(text, " ")[0])
	j, _ := strconv.Atoi(strings.Split(text, " ")[1])
	min := findMinimum(root, i, j)
	fmt.Printf("Minimum %d\n", min)

}
