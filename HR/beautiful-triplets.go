// https://www.hackerrank.com/challenges/beautiful-triplets
package main
import "fmt"

func main() {
    var n, d int
    fmt.Scanf("%d %d", &n, &d)
    
    if n==1 || n==2 {
        fmt.Println(0)
        return
    }
    
    s := make([]int, n)
    for i:=0; i<n; i++ {
        fmt.Scanf("%d", &s[i])
    }
    c:=0
                    
    for i:=n-1; i>=0; i-- {
        for j:=i-1; j>=0; j-- {            
            if s[i]-s[j]==d {  
                for k:=j-1; k>=0; k-- {
                    if s[j]-s[k] == d{
                        c++
                    }
                }    
            }
        }        
    }
    
    fmt.Println(c)
}
