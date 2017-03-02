//https://www.hackerrank.com/challenges/between-two-sets

package main
import "fmt"

func main() {
    var n, m int
    fmt.Scanf("%d %d", &n, &m)
    
    maxE := -1
    minE := 1<<32-1
      
    a := make([]int, n)
    for i:=0; i<n; i++ {
        fmt.Scanf("%d", &a[i])
        if a[i] > maxE{
            maxE  = a[i]
        }
        if a[i] < minE {
            minE = a[i]
        }
    }
    
    b := make([]int, m)
    for i:=0; i<m; i++ {
        fmt.Scanf("%d", &b[i])
        if b[i] > maxE{
            maxE  = b[i]
        }
        if b[i] < minE {
            minE = b[i]
        }
    }
    
    n_between := 0
    
    for x:=minE; x<=maxE; x++ {
        is_between := true
        for _, e := range a{
            if x%e != 0{
                is_between = false    
                break
            }     
        }        
        
        for _, e := range b{
            if e%x != 0{
                is_between = false    
                break
            }
        }
        
        if is_between {
            n_between++
        }
    }
    
    fmt.Println(n_between)
    
}
