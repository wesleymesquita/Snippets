//https://www.hackerrank.com/challenges/jumping-on-the-clouds
package main
import "fmt"

type Node struct {
    Val int
    Next *Node
}

type List struct {
    Head *Node
    Last *Node
}

func main() {
    var n int
    fmt.Scanf("%d", &n)
   
    var list List     
    
    for i:=0; i<n; i++ {
        var t int
        fmt.Scanf("%d", &t)
        
        if t == 0 {
            if list.Head == nil{
                list.Head = &Node{i, nil}
                list.Last = list.Head
            } else{
                pn := &Node{i, nil}
                list.Last.Next = pn
                list.Last = pn
            }
        }
    }      
    
    np := list.Head
    s := 0
    for np != list.Last {
        if np.Next != list.Last && np.Next.Next.Val-np.Val == 2 {
            np = np.Next.Next    
        } else{
            np = np.Next
        }
        s++
    }
    
    fmt.Println(s)
}


