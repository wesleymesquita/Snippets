//https://www.hackerrank.com/challenges/repeated-string
package main
import "fmt"

func main() {
    var s string
    fmt.Scanf("%s", &s)
    
    var n int
    fmt.Scanf("%d", &n)
 
    na := 0        
    for i:=0; i<len(s); i++ {
        if s[i] == byte('a') {
            na++
        } 
    }    

    c := na*(n/len(s))
   
    for i:=0; i<n%(len(s)); i++ {
        if s[i] == byte('a') {
            c++
        } 
    }
   
    fmt.Println(c)        
    
}
