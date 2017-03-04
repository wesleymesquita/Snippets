//https://www.hackerrank.com/challenges/beautiful-days-at-the-movies
package main
import ("fmt"
        "strconv"
        "math"
       )

func main() {
    var i, j, k int
    fmt.Scanf("%d %d %d", &i, &j, &k)
    b := 0
    for x:=i; x<=j; x++{
        n := fmt.Sprintf("%d", x)
        r := make([]byte , len(n))
        for j:=len(n)-1; j>=0; j-- {
            r[len(n)-1-j]=n[j]
        }
                
        if v,error := strconv.Atoi(string(r)); error==nil && int(math.Abs(float64(v-x)))%k==0{
            b++
        }
    }
    fmt.Println(b)
}
