// https://www.hackerrank.com/challenges/non-divisible-subset
package main
import "fmt"

func main() {
    var n,k int
    fmt.Scanf("%d %d", &n, &k)
    a := make(map[int]int, n)
    for i:=0; i<n; i++{
        var m int
        fmt.Scanf("%d", &m)
        a[m%k]++
    }
    
    count := 0    
    for i,_ := range a {
        if i == 0 && a[i] > 0  {
            a[i]=1
        } else if k%2 == 0 && i == k/2 && a[i] > 0 {
            a[i]=1
        } else{
            if _, ok := a[k-i]; ok && a[i]!=-1 && a[k-i]!=-1 {
                if a[i] > a[k-i] {
                    a[k-i]=-1
                } else{
                    a[i]=-1
                }
            }     
        }
    }
    
    
    for _,v := range a {
        if v != -1 {
            count += v
        } 
    } 
    
    fmt.Println(count)
    
}
