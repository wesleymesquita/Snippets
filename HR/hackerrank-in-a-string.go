// https://www.hackerrank.com/challenges/hackerrank-in-a-string
package main
import "fmt"

func main() {
    
    const hr = "hackerrank"
    
    var q int
    fmt.Scanf("%d", &q)
    for q > 0 {
        var s string
        fmt.Scanf("%s", &s)
        found := true
        
        if len(s) < len(hr) {
            found = false
        }
        
        if found {
            j := 0
            for i:=0; i<len(hr); i++ {
                
                if j > len(s) {
                    found = false
                    break
                }
                               
                for j<len(s) && hr[i] != s[j] {
                    j++
                }                 
                j++                
            }            
        }
        
        if found {
            fmt.Println("YES")
        } else{
            fmt.Println("NO")
        }
        
        q--
    }
}
