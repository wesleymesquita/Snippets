// https://www.hackerrank.com/challenges/cats-and-a-mouse
package main
import ("fmt"
       "math")

func main() {
    var q int
    fmt.Scanf("%d", &q)
    for q>0 {
        var a,b,c int
        fmt.Scanf("%d %d %d", &a, &b, &c)
        da := math.Abs(float64(a-c))
        db := math.Abs(float64(b-c))
        if da < db {
            fmt.Println("Cat A")
        }else if da > db {
            fmt.Println("Cat B")
        }else{
            fmt.Println("Mouse C")
        }               
        q--
    }      
}
