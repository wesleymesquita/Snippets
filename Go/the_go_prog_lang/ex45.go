// Exercise 4.5 from The Go Programming Language
// Note : It is not working yet, I didn't find a way to do fully in place management
package main

import ("fmt"
	"os"
	"bufio"
	"strings"
)

func main(){
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	input := strings.Split(scanner.Text(), " ")
	fmt.Println("Before", input)
	removeDups(input)
	fmt.Println("After", input)
}
func removeDups(input []string){
	i := 1
	for i<len(input) {
		if i > 0 {
			if input[i] == input[i-1] {
				input = append(input[:i], input[i+1:]...)
				input[len(input)-1]=""
			}else{
				i++
			}
		}
	}
	

}
