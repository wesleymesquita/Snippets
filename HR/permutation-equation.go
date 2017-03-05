// https://www.hackerrank.com/challenges/permutation-equation
package main
import "fmt"

func main() {
    var n int
    fmt.Scanf("%d", &n)
    p := make([]int, n+1)
    m := make(map[int]int) 
    for i:=1; i<=n; i++ {
        fmt.Scanf("%d", &p[i])
        m[p[i]]=i
    }
    
    for i:=1; i<=n; i++ {
        y := i
        fmt.Println(m[m[y]])    
    }
    
}
