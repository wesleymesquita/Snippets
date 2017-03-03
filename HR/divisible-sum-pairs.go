// https://www.hackerrank.com/challenges/divisible-sum-pairs
package main
import "fmt"

/*1 3 2 6 1 2
1 0 2 0 1 2

0 -> 2 - 
1 -> 2
2 -> 2
*/

func fac(i int) int{
    if i == 1 || i == 0 {
        return 1
    } else{
        return i*fac(i-1)
    }
}

func main() {
    var n, k int
    fmt.Scanf("%d %d", &n, &k)
    a := make([]int,n)
    for i:=0; i<n; i++ {
        fmt.Scanf("%d", &a[i])
        a[i]%=k
    } 
    ma := make(map[int]int)
    for i:=0; i<n; i++ {
        ma[a[i]]++
    }
    pairC := 0
    if ma[0] == 2 {
        pairC++    
    }else if ma[0] >= 2{
        pairC += fac(ma[0])/(fac(ma[0]-2)*2)       
    }
    
    if k%2 == 0 {
        if ma[k/2] == 2 {
            pairC++    
        }else if ma[k/2] >= 2{
            pairC += fac(ma[k/2])/(fac(ma[k/2]-2)*2)            
        }
    }      
    
    for i:=1; i<=k-1; i++ {
        if _, ok := ma[k-i]; ok && k-i!=i && ma[i]!=-1 && ma[k-i]!=-1 {
            pairC += ma[i]*ma[k-i]
            ma[k-i] = -1
            ma[i] = -1
        }    
    }
    
    fmt.Println(pairC)
    
}
