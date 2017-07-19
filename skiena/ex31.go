package main

import "fmt"

func checkParentheses(s string) bool {
	// consider empty string as valid...
	if len(s) == 0 {
		return true
	}
	if len(s) == 1 {
		return false
	}
	bs := []byte(s)
	stack := make([]byte, 0)
	for _, v := range bs {
		if v == '(' {
			stack = append(stack, v)
		} else if v == ')' {
			if len(stack) == 0 {
				return false
			}
			if stack[len(stack)-1] != '(' {
				return false
			} else {
				stack = stack[:len(stack)-1]
			}
		}
	}
	return len(stack) == 0
}

type testInstance struct {
	Content   string
	ExpResult bool
}

func (t testInstance) String() string {
	return fmt.Sprintf("Test %s : Expected %t", t.Content, t.ExpResult)
}

func test(input []testInstance) bool {
	res := make([]bool, len(input))
	for i, v := range input {
		r := checkParentheses(v.Content)
		res[i] = r
	}
	for i, v := range input {
		if v.ExpResult != res[i] {
			fmt.Printf("Failed at test %s\n", v.String())
			return false
		}
	}
	return true
}

func main() {
	tests := []testInstance{
		{"(())", true},
		{"", true},
		{")", false},
		{"(()", false},
		{"())", false},
	}
	fmt.Printf("Final Result: %t\n", test(tests))
}
