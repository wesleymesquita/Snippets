// https://www.hackerrank.com/challenges/mars-exploration
package main
import "fmt"

func main() {
    var s string
    fmt.Scanf("%s", &s)

    ns := len(s) 
    c :=0
    
    for i:=0; i<ns; i=i+3 {
        if s[i] != 'S'{
            c++
        }
        if s[i+1] != 'O'{
            c++
        }
        if s[i+2] != 'S'{
            c++
        }
    }
    fmt.Println(c)
    
}
