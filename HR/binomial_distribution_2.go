// https://www.hackerrank.com/challenges/s10-binomial-distribution-2
package main
import ("fmt"
        "math")

func fac(i int) int{
    if i == 0 || i == 1 {
        return 1
    } else {
        a := i * fac(i-1)
        return a
    }
}

func comb(n,m int) int{
    a := fac(n)/(fac(n-m)*fac(m))        
    return a
}

func main() {
    var a int
    var b int    
    fmt.Scanf("%d %d", &a, &b)
    pr := float64(a)/100.0
    // No more then 2 reject, ie, 1 or 2 rejects 
    prob1 := 0.0
    for i := 0; i<=2; i++ {        
        prob1 +=  float64(comb(b,i))*math.Pow(pr,float64(i))*math.Pow((1-pr), float64(b-i))        
    }

    // At least 2 reject, ie, 1 or 2 or ... or 10 accepts 
    prob2 := 0.0
    for i := 2; i<=b; i++ {
        prob2 +=  float64(comb(b,i))*math.Pow(pr,float64(i))*math.Pow((1-pr), float64(b-i))
    }
    fmt.Printf("%.3f\n%.3f", prob1, prob2)
    
}