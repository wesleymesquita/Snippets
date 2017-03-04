//https://www.hackerrank.com/challenges/bon-appetit
package main
import "fmt"

func main() {
    var n, k int
    fmt.Scanf("%d %d", &n, &k)
    c := make([]int, n)
    for i:=0; i<n; i++{
        fmt.Scanf("%d", &c[i])        
    }
    var bcharged int
    fmt.Scanf("%d", &bcharged)
    
    bcost := 0
    for i:=0; i<n; i++ {
        if i != k {
            bcost += c[i]
        }
    }
    
    ref := bcharged - bcost/2
    
    if ref == 0 {
        fmt.Println("Bon Appetit")
    }else{
        fmt.Println(ref)
    }
    
}
