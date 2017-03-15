// https://www.hackerrank.com/challenges/migratory-birds
package main
import "fmt"

func main() {
    var n int 
    fmt.Scanf("%d", &n)
    
    m := make(map[int]int)
    
    for i:=0; i<n; i++ {
        var t int
        fmt.Scanf("%d", &t)
        m[t]++
    }
    
    max := -1
    maxK := 0
    
    for k, v := range m {
        if v > max {
            max = v
            maxK = k
        }else if v == max {
            if k < maxK  {
                maxK = k
            }
        }
    }
    
    fmt.Println(maxK)
    
}
