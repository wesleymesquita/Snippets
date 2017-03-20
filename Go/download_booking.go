package main

import (
	"io/ioutil"
	"log"
	"net/http"
	"regexp"
	"strings"
)

const (
	defaultURL = "https://www.booking.com"
)

type URL struct {
	addr string
}

func getCountries() []string {
	const (
		defaultCountriesFile = "countries.txt"
	)

	bf, err := ioutil.ReadFile(defaultCountriesFile)
	if err == nil {
		return strings.Split(string(bf), "\n")
	}
	log.Println("Not found locally. We will try to get from Web")
	const (
		countriesURL = "http://www.listofcountriesoftheworld.com/"
	)

	resp, err := http.Get(countriesURL)
	if err != nil {
		log.Fatal("Could not retrieve courntry list")
		return nil
	}

	bf, err = ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Fatal("Could not read countries url")
		return nil
	}
	log.Println(string(bf))
	exp, err := regexp.Compile("<a href=\"[a-z]+.html\">([A-Z][a-z]+)</a>")
	log.Println(exp)
	if err != nil {
		log.Fatal("Check internal Regex")
		return nil
	}

	res := exp.FindAllStringSubmatch(string(bf), 1000)
	log.Println("Found", len(res), " entries")
	filtered := make([]string, 0)
	for _, s := range res {
		log.Println(s[1])
		filtered = append(filtered, s[1])
	}
	err = ioutil.WriteFile(defaultCountriesFile, []byte(strings.Join(filtered, "\n")), 0644)
	if err != nil {
		log.Println("Could not flush, country list", err)
	}

	return filtered
}

func craw(url URL) ([]URL, error) {
	resp, err := http.Get(url.addr)
	if err != nil {
		log.Fatal("Could not access", url.addr)
		return nil, err
	} else {
		defer resp.Body.Close()
		bf, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			log.Fatal("Could not read", url.addr)
			return nil, err
		}
		log.Println(string(bf))
	}
	return nil, nil
}

func main() {
	getCountries()
	//	craw(URL{addr: defaultURL})
}
