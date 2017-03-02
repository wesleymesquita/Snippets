// https://www.hackerrank.com/challenges/grading
package main
import "fmt"

func round(g int) int {
    if g < 38{
        return g
    }else{
        if (g+1)%5==0 {
            return g+1
        }else if (g+2)%5 == 0 {
            return g+2
        }else{
            return g
        }     
        
    }
}   

func main() {
    var n int
    fmt.Scanf("%v", &n)
    for i:=0; i<n; i++{
        var g int
        fmt.Scanf("%v", &g)
        fmt.Println(round(g))        
    }
    
    //Enter your code here. Read input from STDIN. Print output to STDOUT
}
