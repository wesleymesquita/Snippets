// https://www.hackerrank.com/challenges/picking-numbers
package main
import ("fmt"
        "sort")

func main() {
    var n int 
    fmt.Scanf("%d", &n)
    
    if  n == 1 {
        fmt.Println("1")
        return
    }
    
    a := make([]int, n)
    for i:=0; i<n; i++{
        fmt.Scanf("%d", &a[i])
    }
    sort.Ints(a)
    cMax :=1
    for i:=n-1; i>=0; i--{
        c := 1
        for j:=i-1; j>=0; j--{
            if a[i]-a[j] <= 1{
                c++
            } else{
                break
            }
        }
        if c > cMax {
            cMax = c
        }
    }
    
    fmt.Println(cMax)

}
