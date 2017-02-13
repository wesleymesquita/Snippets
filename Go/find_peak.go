package main

import (
	"fmt"
	"os"
)

func main() {
	numbers := read_info()
	print_info(&numbers)
	peak := -1
	if len(numbers) == 0 {
		fmt.Println("Size 0 : it is not allowed")
	} else if len(numbers) == 1 {
		fmt.Println("0")
	} else {
		for i := 0; i < len(numbers); i++ {
			if i == 0 {
				if numbers[i] >= numbers[i+1] {
					fmt.Println(" i == 0")
					peak = i
					break
				}
			} else if i == len(numbers)-1 {
				if numbers[i] >= numbers[i-1] {
					fmt.Println(" i == len-1")
					peak = i
					break
				}
			} else if i != len(numbers)-1 {
				if numbers[i-1] <= numbers[i] && numbers[i+1] <= numbers[i] {
					fmt.Println("INDEX == ", i)
					peak = i
					break
				}
			}
		}
	}

	fmt.Println(peak)
}
func print_info(data *[]int) {
	fmt.Println(len(*data), "---", *data)
}

func read_info() []int {
	numbers := make([]int, 0)
	var i, n int
	_, err := fmt.Scanf("%d\n", &n)
	if err != nil {
		fmt.Println("Had a problem: ", err)
		os.Exit(1)
	}
	for j := 0; j < n; j++ {
		_, err = fmt.Scanf("%d\n", &i)
		if err != nil {
			fmt.Println("Had an issue", err)
		}
		numbers = append(numbers, i)
	}
	return numbers
}
