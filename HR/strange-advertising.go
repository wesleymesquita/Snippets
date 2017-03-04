// https://www.hackerrank.com/challenges/strange-advertising
package main
import "fmt"

func main() {
    var n int
    fmt.Scanf("%d", &n)
    f := 2
    f1 := (5/2)*3
    for i:=1; i<n; i++{
    
        f += f1/2
        f1 = (f1/2)*3
    }
    fmt.Println(f)
}
