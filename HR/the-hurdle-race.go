//https://www.hackerrank.com/challenges/the-hurdle-race
package main
import "fmt"

func main() {
    var n,k int
    fmt.Scanf("%d %d", &n,&k)
    m := 0
    for i:=0; i<n; i++ {
        var h int
        fmt.Scanf("%d", &h)
        if h > k {
            m+= h-k
            k+=h-k
        }
    }
    fmt.Println(m)
}
