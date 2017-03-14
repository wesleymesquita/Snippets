//https://www.hackerrank.com/challenges/weighted-uniform-string
package main
import "fmt"

func main() {

    var s string
    fmt.Scanf("%s", &s)
    
    var n int
    fmt.Scanf("%d", &n)
    
    m := make(map[int]bool)
    
    sz := len(s)
    for i:=0; i<sz; i++ {                
        w := ( int( byte(s[i])-byte('a') ) + 1 )
        m[w] = true        
        pos := 1                        
        for  (i+pos) <sz && s[i+pos] == s[i]  {
            mw := w*(pos+1) 
            m[mw] = true     
            pos++
        }                
        i = i+pos-1
    }

    for i:=0; i<n; i++ {
        var x int     
        fmt.Scanf("%d", &x)
        if _, ok := m[x]; ok {
            fmt.Println("Yes")
        }else{
            fmt.Println("No")
        }  
    }
}
