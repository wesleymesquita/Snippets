// https://www.hackerrank.com/challenges/s10-geometric-distribution-1
package main
import "fmt"

func main() {
    
    var a,b int 
    fmt.Scanf("%d %d", &a, &b)
    p := float64(a)/ float64(b)
    var n int
    fmt.Scanf("%d", &n)
    r := 1.0
    for i:=1; i<n; i++{
        r *= (1-p)
    }
    r *= p
    fmt.Printf("%.3f", r)
 }