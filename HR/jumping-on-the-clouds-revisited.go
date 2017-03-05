// https://www.hackerrank.com/challenges/jumping-on-the-clouds-revisited
package main
import "fmt"

func main() {
    var n, k int 
    fmt.Scanf("%d %d", &n, &k)
    c := make([]int, n)
    
    for i :=0; i<n; i++{
        fmt.Scanf("%d", &c[i])
    }
    
    E := 100 
    p := 0
    for E >= 0 {
        np := (p+k)%n
        E--
        
        if c[np] == 1{
            E-=2
        }
        
        //fmt.Println(np, E)
        
        if np == 0 || E == 0{
            fmt.Println(E)
            break
        }
        p = np    
    } 
}
