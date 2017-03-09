// https://www.hackerrank.com/challenges/reduced-string
package main
import "fmt"


func main() {
    var s string 
    fmt.Scanf("%s", &s)
        
    sb := []byte(s)
    
    for {
        deleted := false
        sz := len(sb)            
        
        if sz == 2 &&  sb[0]== sb[1]{
            sb[0], sb[1] = byte('X'), byte('X')
            deleted = true
        } else if len(sb) > 2 { 
            for i:=1; i<sz; i++ {
                if sb[i-1] == sb[i] {
                    sb[i-1], sb[i] = byte('X'), byte('X')
                    deleted = true
                } 
            }
        }
          
        if deleted {
            nsb := make([]byte, 0)
            for i:=0; i<sz; i++{
                if sb[i] != byte('X'){
                    nsb = append(nsb, sb[i])
                }
            }
            sb = nsb
            
        } else{
            break
        }
    }
    if len(sb) == 0 {
        fmt.Println("Empty String")
    }else{
        fmt.Println(string(sb))    
    }
    
    
 
}
