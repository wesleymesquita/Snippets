//https://www.hackerrank.com/challenges/save-the-prisoner
package main
import "fmt"

func main() {
    var t int
    fmt.Scanf("%d", &t)
    for t >0 {
        t--
        var n,m,s int
        fmt.Scanf("%d %d %d", &n,&m,&s)       
        s--
        s = s+m-1
        if s <= n-1 {
            fmt.Println(s+1)
        } else{
            fmt.Println(s%n+1)
        }
    }
}
