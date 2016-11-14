package main
import ("fmt"
        "math")
            
func fac(n int) int{
    if n == 1 || n == 0 {
        return 1
    } else {
        r := n*fac(n-1)
        return r
    }
}

func comb(n,m int) int {
    if n == m {
        return 1
    } else {
        r := fac(n)/(fac(n-m)*fac(m))
        return r        
    }
}

func main() {
    var a float64
    var b float64 
    fmt.Scanf("%f %f", &a, &b)
    p :=  a/(a+b)
    c := 0.0
    for i:=3; i<=6; i++{        
        r := float64(comb(6,i)) * math.Pow(p, float64(i)) * math.Pow((1.0-p), float64(6-i))                 
        c += r
    }
    
    fmt.Printf("%.3f",c)
}