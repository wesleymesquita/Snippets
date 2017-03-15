// https://www.hackerrank.com/challenges/drawing-book
package main
import ("fmt"
        "math"
       )

func main() {
    var n, p int 
    fmt.Scanf("%d", &n)
    fmt.Scanf("%d", &p)
    
    if p == 1 || p == n {
        fmt.Println("0")
        return
    }
   
    fromBeg := true
    if math.Abs(float64(1-p)) >= math.Abs(float64(n-p)){
        fromBeg = false
    }    
       
    if fromBeg {
        fmt.Println((p/2))       
    }else{ 
        fmt.Println((n-p)/2)    
    }
    
}
