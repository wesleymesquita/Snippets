// https://tour.golang.org/moretypes/26
package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
	n := -1 	
	return func () int {
		n++	
		if n == 0{
			return 0
		}else if n == 1 {
			return 1
		}else{
			a := make([]int, n+1)
		  	a[0] = 0
			a[1] = 1
			for i:=2; i<=n; i++ {
				a[i] = a[i-1] + a[i-2]
			}
			return a[n]
		}
	}
}

func main() {
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}

