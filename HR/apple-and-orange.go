//https://www.hackerrank.com/challenges/apple-and-orange
package main
import "fmt"

type House struct {
    s, t int
}

func (h House) fallIn(d int) bool {       
    
    if d >= h.s && d <=h.t {
        return true
    }    
    return false
}    


func main() {
    var s, t int
    fmt.Scanf("%d %d", &s, &t)
    
    h:= House{s,t}    
    
    var a,b int
    fmt.Scanf("%d %d", &a, &b)
    
    var m, n int
    fmt.Scanf("%d %d", &m, &n)
    
    apples := 0
    oranges := 0
    
    for i:=0; i<m; i++ {
        var dapple int
        fmt.Scanf("%d", &dapple)        
        if h.fallIn(a + dapple) {
            apples++
        }
    } 
        
    for i:=0; i<n; i++ {
        var dorange int
        fmt.Scanf("%d", &dorange)        
        if h.fallIn(b+dorange) {
            oranges++
        }
    }
    
    fmt.Printf("%d\n%d", apples, oranges)
    
}

