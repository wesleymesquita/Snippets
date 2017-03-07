// https://www.hackerrank.com/challenges/equality-in-a-array
package main
import "fmt"

func main() {
    var n int
    fmt.Scanf("%d", &n)
    
    a := make(map[int]int)
    
    for i:=0; i<n; i++ {
        var t int
        fmt.Scanf("%d", &t)
        a[t]++
    }
    max := -1
    for _,v := range a {
        if v > max {
            max = v
        }
    } 
   
    fmt.Println(n-max)   
}
