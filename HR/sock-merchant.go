// https://www.hackerrank.com/challenges/sock-merchant
package main
import "fmt"

func main() {
    var n int
    fmt.Scanf("%d", &n)
    c := make(map[int]int, n)
    for i:=0;i<n; i++{
        var cl int
        fmt.Scanf("%d", &cl)        
        c[cl]++
    }
    p := 0
    for _,v := range c {
        p+= v/2 
    }
    fmt.Println(p)
    
}
