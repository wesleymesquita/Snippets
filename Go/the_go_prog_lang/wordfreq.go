package main

import ( "os"
	"bufio"
	"log"
	"fmt"
)
func main(){
	if len(os.Args) != 2 {
		log.Println("Wrong args number : use wordfreq [file path]")
		os.Exit(1)
	}
	f , err := os.Open(os.Args[1])
	if err != nil {
		log.Println("Had a problem to open file", os.Args[1])
	}
	
	scanner := bufio.NewScanner(f)
	scanner.Split(bufio.ScanWords)
	wordCount := make(map[string]int)
	for scanner.Scan() {
		word := scanner.Text()
		wordCount[word]++
	}
	for k,v := range wordCount {
		fmt.Println(k, "\t", v)
	}


	f.Close()
}
