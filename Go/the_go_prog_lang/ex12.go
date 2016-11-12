package main

import ("fmt"
        "os")


func main(){
  fmt.Println("Arg Index\tArg")
  for i, arg := range os.Args[1:]{
      fmt.Printf("%d\t\t%s\n", i, arg)
  }
}
