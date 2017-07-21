package main

import (
	"fmt"
	"time"
)

type DynamicArray struct {
	Capacity int
	arr      []int
	Last     int
}

func NewDynamicArray() *DynamicArray {
	return &DynamicArray{Capacity: 1, Last: -1, arr: []int{0}}
}

func (d *DynamicArray) expand() {
	d.Capacity *= 2
	newArr := make([]int, d.Capacity)
	for i, _ := range d.arr {
		newArr[i] = d.arr[i]
	}
	d.arr = newArr
}

func (d *DynamicArray) Add(elem int) {
	if d.Last == d.Capacity-1 {
		d.expand()
	}
	d.Last++
	d.arr[d.Last] = elem
}

func (d *DynamicArray) Remove() int {
	if len(d.arr) != 0 {
		d.Last--
		return d.arr[d.Last+1]
	}
	return -1
}

func populateArray(quantity int) {
	arr := NewDynamicArray()
	t := time.Now()
	for i := 0; i < quantity; i++ {
		// Could be value here, as simple, the best. I want just to probe insertion time
		arr.Add(1)
	}
	t2 := time.Since(t)
	// print the average time to insert one element
	fmt.Printf("Cap:%d\t\t\t Size:%d\t\t\t\t. Time/Size:%f\n", arr.Capacity, quantity, float64(t2)/float64(quantity))
}

func main() {
	for i := 1; i < 1<<29; i += 10000000 {
		populateArray(i)
		// Not sure if it makes sense for golang, but I want to give room for 'populateArray' to
		// have room to deallocate resources.
		time.Sleep(500 * time.Millisecond)
	}
}
