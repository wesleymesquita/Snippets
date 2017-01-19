// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 112.
//!+

// Issues prints a table of GitHub issues matching the search terms.
package main

import (
	"fmt"
	"log"
	"os"
	"time"
	"gopl.io/ch4/github"
)

//!+
func main() {
	result, err := github.SearchIssues(os.Args[1:])
	if err != nil {
		log.Fatal(err)
	}
	fmt.Printf("%d issues:\n", result.TotalCount)
	lessThanAMonth := make([]*github.Issue,0)
	lessThanAYear := make([]*github.Issue,0)
	moreThanAYear := make([]*github.Issue,0)
	oneMonth, err := time.ParseDuration("720h")

	if err != nil {
		log.Println("Error to parse duration")	
		os.Exit(1)
	}
	fmt.Println("One month == ", oneMonth.Seconds())	
	oneYear, err := time.ParseDuration("8760h")
	if err != nil {
		log.Println("Error to parse duration")	
		os.Exit(1)
	} 

	fmt.Println("One Year == ", oneYear.Seconds())	
	for _, item := range result.Items {
		dur := time.Since(item.CreatedAt).Seconds() 
		fmt.Println("Dur == ", dur, " Date == ", item.CreatedAt)
		if dur < oneMonth.Seconds() {
			lessThanAMonth = append(lessThanAMonth, item)
		}else if dur < oneYear.Seconds(){
			lessThanAYear = append(lessThanAYear, item)
		}else{
			moreThanAYear = append(moreThanAYear, item)
		}
	}
	fmt.Println("Tickets less than a month older")
	for _, item := range lessThanAMonth{
		fmt.Printf("[%v] #%-5d %9.9s %.55s\n",
			item.CreatedAt, item.Number, item.User.Login, item.Title)
	}	
	fmt.Println("Tickets less than a year (and greater than a month) older")
	for _, item := range lessThanAYear {
		fmt.Printf("[%v] #%-5d %9.9s %.55s\n",
			item.CreatedAt, item.Number, item.User.Login, item.Title)
	}	
		fmt.Println("Tickets more than a year older")
			for _, item  :=range moreThanAYear{
				fmt.Printf("[%v] #%-5d %9.9s %.55s\n",
					item.CreatedAt, item.Number, item.User.Login, item.Title)
			}	
}

//!-

/*
//!+textoutput
$ go build gopl.io/ch4/issues
$ ./issues repo:golang/go is:open json decoder
13 issues:
#5680    eaigner encoding/json: set key converter on en/decoder
#6050  gopherbot encoding/json: provide tokenizer
#8658  gopherbot encoding/json: use bufio
#8462  kortschak encoding/json: UnmarshalText confuses json.Unmarshal
#5901        rsc encoding/json: allow override type marshaling
#9812  klauspost encoding/json: string tag not symmetric
#7872  extempora encoding/json: Encoder internally buffers full output
#9650    cespare encoding/json: Decoding gives errPhase when unmarshalin
#6716  gopherbot encoding/json: include field name in unmarshal error me
#6901  lukescott encoding/json, encoding/xml: option to treat unknown fi
#6384    joeshaw encoding/json: encode precise floating point integers u
#6647    btracey x/tools/cmd/godoc: display type kind of each named type
#4237  gjemiller encoding/base64: URLEncoding padding is optional
//!-textoutput
*/
