//https://www.hackerrank.com/challenges/camelcase
package main
import ("fmt"
        "strings"
       )

func main() {
    var s string
    fmt.Scanf("%s", &s)
    
    us := strings.ToUpper(s)
    
    wc := 1
    for i:=0; i<len(s); i++{
        if s[i] == us[i] {
            wc++
        }
    }
    
    fmt.Println(wc)
}
