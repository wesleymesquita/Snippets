// https://www.hackerrank.com/challenges/minimum-distances
package main
import ("fmt"
       "sort")

func main() {
    var n  int
    fmt.Scanf("%d", &n)
    m := make(map[int][]int)
      
    for i:=0; i<n; i++ {     
        var t int
        fmt.Scanf("%d", &t)
        if m[t] == nil {
            m[t] = make([]int, 0)
        }
        m[t] = append(m[t], i) 
    }
    
    minD := 1<<31
    for k, _ := range m{
        sort.Ints(m[k])
        for i:=1; i<len(m[k]); i++ {
            if m[k][i]-m[k][i-1] < minD {
                minD = m[k][i]-m[k][i-1]
            }
        }        
    } 
    
    if minD == 1<<31 {
        fmt.Println(-1)
    }else{
        fmt.Println(minD)
    }
}
