//https://www.hackerrank.com/challenges/queens-attack-2
// TODO : Not passing all tests. Getting runtime error, but could not replicate.

package main
import "fmt"


type ChessBoard struct {
    n, Rq, Cq int   
    b [][]int
}

func (cb *ChessBoard) Init(n, rq, cq int) {
    cb.n = n
    cb.Rq = rq
    cb.Cq = cq
        
    cb.b = make([][]int, n+1)
            
    for i:=0; i<=n; i++ {
        cb.b[i] = make([]int, n+1)        
        cb.b[i][0] = i
    }        
    
    for j:=1; j<=n; j++ {
        cb.b[0][j] = j
    }
    
    cb.b[rq][cq] = 2
    
}

func (cb *ChessBoard) Mark(r,c int){    
    cb.b[r][c] = 1
}


func (cb *ChessBoard) PrintRow(r int) string{
    return fmt.Sprintln(cb.b[r])
}

func (cb *ChessBoard) String() string {
    s := ""
    for i:=cb.n; i>=0; i-- {
        s += cb.PrintRow(i)
    }
    return s
}

func (cb* ChessBoard) Check() int{
    c := 0
    
    for j:=cb.Cq-1; j>=1; j-- {
        if cb.b[cb.Rq][j] == 1{
            break
        }else{
            c++
        }         
    }    

    
    for i, j :=cb.Rq+1, cb.Cq-1; i<=cb.n && j>=1; i,j=i+1,j-1 {
        if cb.b[i][j] == 1{
            break
        }else{
            c++
        } 
    }
    
   
    for i:=cb.Rq+1; i<=cb.n; i++ {
        if cb.b[i][cb.Cq] == 1{
            break
        }else{
            c++
        }         
    }       
   
   

    
    for i,j := cb.Rq+1,cb.Cq+1; i<=cb.n && j<=cb.n; i,j=i+1,j+1 {        
        if cb.b[i][j] == 1{
            break
        }else{
            c++
        }         
    }
   
     
    for j:=cb.Cq+1; j<=cb.n; j++ {
        if cb.b[cb.Rq][j] == 1{
            break
        }else{
            c++
        }         
    }
   
   
    
    for i,j:=cb.Rq-1,cb.Cq+1; i>=1 && j<=cb.n; i,j=i-1,j+1 {        
        if cb.b[i][j] == 1{
            break
        }else{
            c++
        }         
    }
   
    
    for i:=cb.Rq-1; i>=1; i-- {
        if cb.b[i][cb.Cq] == 1{
            break
        }else{
            c++
        }         
    }
    
    for i, j:=cb.Rq-1, cb.Cq-1; i>=1 && j>=1; i,j=i-1,j-1 {        
        if cb.b[i][j] == 1{
            break
        }else{
            c++
        }         
    }
    
    return c
} 

func main() {
    var n, k int
    fmt.Scanf("%d %d", &n, &k)
    
    var rq, cq int
    fmt.Scanf("%d %d", &rq, &cq)
    
    
    cb := ChessBoard{}
    cb.Init(n, rq, cq)
    
    
    for i:=0; i<k; i++ {
        var r, c int
        fmt.Scanf("%d %d", &r, &c)
        cb.Mark(r,c) 
    }
    fmt.Println(cb.Check())
   
}
