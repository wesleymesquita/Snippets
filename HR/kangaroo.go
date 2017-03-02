//https://www.hackerrank.com/challenges/kangaroo
package main
import "fmt"

func main() {
    var x1, v1, x2, v2 int
    fmt.Scanf("%d %d %d %d", &x1, &v1, &x2, &v2)
    if v1 == v2 {
        if  x1 == x2 {
            fmt.Print("YES")
        }else{
            fmt.Print("NO")
        }
    } else{
        j := (float64(x2)-float64(x1))/(float64(v1)-float64(v2))
        if j >= 0 && float64(int(j)) == j{
            fmt.Println("YES")
        }else{
            fmt.Println("NO")
        }
    }        

}
