// This Merge Sort implementation is based the one at 
// 'Introduction to Algorithms from Cormen at al, 3rd Edition 
// The idea from this snippet is to get if it is possible to get
// some immediate benefit from go routines with little extra code 
package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
	"sort"
)
// This is an exact copy of impl from Cormen
func merge(A []int, p, q, r int) {

	n1 := q - p + 1
	n2 := r - q
	L := make([]int, n1+1)
	R := make([]int, n2+1)
	for i := 0; i < n1; i++ {
		L[i] = A[p+i]
	}
	for i := 0; i < n2; i++ {
		R[i] = A[q+i+1]
	}
	L[n1] = math.MaxInt32
	R[n2] = math.MaxInt32

	i := 0
	j := 0
	for k := p; k <= r; k++ {
		if L[i] <= R[j] {
			A[k] = L[i]
			i++
		} else {
			A[k] = R[j]
			j++
		}
	}
}


func mergeSort(A []int, p, r int) {
	if p < r {
		q := (p+r)/2
		mergeSort(A,p,q)
		mergeSort(A,q+1, r)
		merge(A, p,q,r)
	}
}

func mergeSortGoRoutine(A []int, p, r int) {
	if p < r {
		q := (p+r)/2
		c1 := make(chan int)
		c2 := make(chan int)

		go func(A []int, p, r int, c chan int) {
			// using here 'mergeSortGoRoutine would create a huge
			// CPU overhead and deteriorate performance. Doing this 
			// way below, I saw some improvement in sorting time
			mergeSort(A, p, r)
			c <- 0
		}(A, p, q, c1)

		go func(A []int, p, r int, c chan int) {
			mergeSort(A,p,r)
			c <- 0
		}(A, q+1, r, c2)

		<-c1
		<-c2
		merge(A,p,q,r)
	}
}

func  mergeSort_test(n int) (time.Duration, time.Duration){
	rand.Seed(17)
	A := make([]int, n)
	for i:=0; i<n; i++ {
		A[i] = rand.Intn(n)
	}
	B := make([]int, n)
	copy(B, A)

	t1 := time.Now()
	mergeSort(A, 0, n-1)
	t2 := time.Now()
	
	// Note : usually I don't use 'panic', but this is only 
	// a small snippet.
	if !sort.IntsAreSorted(A){
		panic("mergeSorte is not sorting!")
	}
	t3 := time.Now()
	mergeSortGoRoutine(B, 0, n-1)
	t4 := time.Now()
	if !sort.IntsAreSorted(B){
		panic("mergeSortGoRoutine is NOT sorting!")
	}

	return t2.Sub(t1), t4.Sub(t3)
}

func main() {
	for i:=1; i<=10000000; i*=10 {
		d1, d2 := mergeSort_test(i)
		fmt.Printf("Size %d |\t %v |\t %v |\t%v\n", i, d1.Seconds(), d2.Seconds(), 100.0*(d2.Seconds()/d1.Seconds()))
	}
}

