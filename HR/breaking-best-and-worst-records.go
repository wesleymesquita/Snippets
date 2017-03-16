// https://www.hackerrank.com/challenges/breaking-best-and-worst-records
package main
import "fmt"

func main() {
    var n int
    fmt.Scanf("%d", &n)
    var maxP, minP int
    
    fmt.Scanf("%d", &maxP)
    minP = maxP
    cMax := 0
    cMin := 0
    
    for i:=1; i<n; i++{
        var t int
        fmt.Scanf("%d", &t)
        if t > maxP {
            maxP = t
            cMax++
        }else if t < minP{
            minP = t
            cMin++
        }  
    }
    
    fmt.Printf("%d %d\n", cMax, cMin)
    
}
