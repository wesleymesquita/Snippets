package main

import "fmt"

type MyDict []bool

func NewMyDict(size int) *MyDict {
	// need to cover 1...n, so need index n. that is why 'size +1'
	vec := MyDict(make([]bool, size+1))
	for i := 0; i < size+1; i++ {
		vec[i] = false
	}
	return &vec
}

func (d *MyDict) Len() int {
	return len([]bool(*d))
}
func (d *MyDict) Search(elem int) (found bool) {
	if elem > d.Len() {
		return false
	}
	return (*d)[elem]
}

func (d *MyDict) Insert(elem int) error {
	if elem > d.Len() {
		return fmt.Errorf("elem %d dont fit in dict", elem)
	}
	(*d)[elem] = true
	return nil
}

func (d *MyDict) Remove(elem int) error {
	if elem > d.Len() {
		fmt.Errorf("elem %d out of range", elem)
	}
	(*d)[elem] = false
	return nil
}

func main() {
	d := NewMyDict(100)
	for i := 1; i <= 100; i++ {
		if err := d.Insert(i); err != nil {
			fmt.Print("Insert error %s\n", err)
		}
	}

	for i := 1; i <= 100; i++ {
		if ok := d.Search(i); !ok {
			fmt.Print("Search error %d\n", i)
		}
	}

	for i := 1; i <= 100; i++ {
		if err := d.Remove(i); err != nil {
			fmt.Print("Remove error %s\n", err)
		}
	}
}
