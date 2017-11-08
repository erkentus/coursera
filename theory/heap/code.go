package main

import "fmt"

func main() {
	h := FromSlice([]int{123, 10, 1, 412, 1, 20, 24, 10})
	n := len(h.data)
	for i := 0; i < n; i++ {
		fmt.Println(h.Pop())
	}
}

type Heap struct {
	data []int
}

func New() *Heap {
	return &Heap{
		data: make([]int, 0),
	}
}

func FromSlice(x []int) *Heap {
	h := &Heap{
		data: x,
	}
	for i := (len(x) - 1) / 2; i >= 0; i-- {
		h.heapify(i)
	}
	return h
}

func (h *Heap) Pop() int {
	if len(h.data) == 0 {
		return 0
	}

	min := h.data[0]
	h.data[0], h.data[len(h.data)-1] = h.data[len(h.data)-1], h.data[0]
	// fmt.Println(h.data[0])
	h.data = h.data[0 : len(h.data)-1]
	h.heapify(0)
	return min
}

func (h *Heap) Top() int {
	return h.data[0]
}

func (h *Heap) Insert(x int) {
	h.data = append(h.data, x)
	i := len(h.data) - 1
	for p := (i - 1) / 2; p != 0; {
		if h.data[p] > h.data[i] {
			h.data[p], h.data[i] = h.data[i], h.data[p]
			i = p
			continue
		}
		break
	}
}

func (h *Heap) heapify(i int) {
	n := len(h.data)
	largest := i
	l := 2*i + 1
	r := 2*i + 2

	if l < n && h.data[largest] > h.data[l] {
		largest = l
	}
	if r < n && h.data[largest] > h.data[r] {
		largest = r
	}

	if largest != i {
		h.data[i], h.data[largest] = h.data[largest], h.data[i]
		h.heapify(largest)
	}
}
