package main

import ("fmt" 
		"time"
		"strings")

func main (){
	
	// Test data
	SIZE := 100000
	S := "S"
	var target string
	data := make([]string, SIZE)
	for i:=0; i<SIZE; i++ {
		data[i] = S
	}
	

	// Simple Concat
	target = ""
	
	fmt.Print("Started to concat... \n")
	t_start_concat := time.Now()	
	for i:=0; i<SIZE; i++ {	
		target += data[i]
	}
	t_end_concat := time.Now()
	fmt.Print("Ended to Concat\n")
	
	fmt.Printf("Final Size == %d \t Time to concat %v\n", len(target), t_end_concat.Sub(t_start_concat))

	// Join 
	target = ""
	
	fmt.Print("Started to Join ...\n")
	t_start_join := time.Now()
	target =  strings.Join(data, "")
	t_end_join := time.Now()	
	fmt.Print("Ended to Join\n")	
	
	fmt.Printf("Final Size = %v. \t Time to coin %v.\n", len(target), t_end_join.Sub(t_start_join))	
}