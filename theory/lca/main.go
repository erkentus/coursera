package main

import (
	"fmt"
	"math"
)

func main() {
	// tree
	tree := make([]int, 0)

	// root is always at 0
	tree = []int{
		-1, // parent of 0
		0,  // parent of 1
		0,  // parent of 2
		0,  // parent of 3
		1,  //parent of 4
		1,  //parent of 5
		2,  //parent of 6
		6,  //parent of 7
		2,  //parent of 8
		7,  //parent of 9
		7,  //parent of 10
	}

	/*

		0______________
		|	   \       \
		|  		\   	\
		1   	2   	3
		| \		| \
		4  5    6  8
				|
				7
				| \
				9  10
	*/

	sqrtImpl := newSqrtLCA(tree)

	assert(sqrtImpl.LCA(0, 0), 0)
	assert(sqrtImpl.LCA(0, 1), 0)
	assert(sqrtImpl.LCA(4, 5), 1)
	assert(sqrtImpl.LCA(4, 2), 0)
	assert(sqrtImpl.LCA(6, 4), 0)
	assert(sqrtImpl.LCA(9, 8), 2)
	assert(sqrtImpl.LCA(9, 6), 6)

	logImpl := newLogLCA(tree)

	assert(logImpl.LCA(0, 0), 0)
	assert(logImpl.LCA(0, 1), 0)
	assert(logImpl.LCA(4, 5), 1)
	assert(logImpl.LCA(4, 2), 0)
	assert(logImpl.LCA(6, 4), 0)
	assert(logImpl.LCA(9, 8), 2)
	assert(logImpl.LCA(9, 6), 6)
}

func assert(x, y int) {
	if x != y {
		panic(fmt.Sprintf("%d != %d", x, y))
	}
	fmt.Println("correct!")
}

// lca implementations
// link: https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/

// SQRT decomposition based implementation
// it splits all nodes into sqrt levels [1..sqrt(h)-1],[sqrt[h],2*sqrt[h]-1]...
// and allows O(sqrt[tree-height]) LCA look ups of any two nodes
type sqrtLCA struct {
	p         []int   // p stores the ancestor at is situated on the previous sqrt level
	h         []int   // indicates the level (non-sqrt) of the node
	parent    []int   // store the child -> parent
	children  [][]int // store the reverse of the tree, i.e. each parent -> child
	maxHeight int
}

// tree stores child -> parent relations in the tree
func newSqrtLCA(tree []int) *sqrtLCA {
	n := len(tree) //number of nodes

	// build the version of tree for traversal
	children := make([][]int, n)
	for child, parent := range tree {
		if parent == -1 {
			continue
		}
		children[parent] = append(children[parent], child)
	}

	// compute the heights
	h := make([]int, n)
	// h[0] = 0

	var stack []int
	stack = append(stack, 0)
	maxHeight := 0

	// first figure out the level of each node and total number of levels
	for len(stack) != 0 {
		cur := stack[0]
		curLvl := h[cur]

		if curLvl > maxHeight {
			maxHeight = curLvl
		}

		stack = stack[1:]
		for _, child := range children[cur] {
			h[child] = curLvl + 1
			stack = append(stack, child)
		}
	}

	sqrtTree := &sqrtLCA{
		h:         h,
		p:         make([]int, n),
		children:  children,
		parent:    tree, // TODO: this slice should be copied
		maxHeight: maxHeight,
	}

	sqrtTree.build(0)

	return sqrtTree
}

// dfs to populate the `p`
func (lca *sqrtLCA) build(cur int) {
	nr := int(math.Floor(math.Sqrt(float64(lca.maxHeight)))) // sqrt(maxHeight), size of each sqrt level block

	if lca.h[cur] < nr { //first sqrt level then we point to the root
		lca.p[cur] = 0
	} else {
		// if we are the first level in the sqrt level, then just point to immediate parent
		if lca.h[cur]%nr == 0 {
			lca.p[cur] = lca.parent[cur]
		} else { //other wise we point to previous block
			lca.p[cur] = lca.p[lca.parent[cur]]
		}
	}

	for _, child := range lca.children[cur] {
		lca.build(child)
	}
}

// LCA of nodes x and y
func (lca *sqrtLCA) LCA(x, y int) int {
	// first make sure we are at the same sqrt level
	for lca.p[x] != lca.p[y] {
		if lca.h[x] > lca.h[y] {
			x = lca.p[x]
		} else {
			y = lca.p[y]
		}
	}

	// now they are on the same sqrt level

	for x != y {
		if lca.h[x] > lca.h[y] {
			x = lca.parent[x]
		} else {
			y = lca.parent[y]
		}
	}

	return x
}

// Log decomposition based implementation
// it stores 2^i ancestors for each nodes for faster skips
// the build stage takes O(n*log(h))
// LCA look up takes O(log(h))
type logLCA struct {
	p        [][]int // p[i][j] stores 2 << j ancestor of node i
	h        []int   // indicates the level of the node
	parent   []int   // store the child -> parent
	children [][]int // store the reverse of the tree, i.e. each parent -> child
}

func newLogLCA(tree []int) *logLCA {
	n := len(tree)
	// build the parent->child version of tree for traversal
	children := make([][]int, n)
	for child, parent := range tree {
		if parent == -1 {
			continue
		}
		children[parent] = append(children[parent], child)
	}

	// compute the heights
	h := make([]int, n)

	var stack []int
	stack = append(stack, 0)

	// figure out the level of each node
	for len(stack) != 0 {
		cur := stack[0]
		curLvl := h[cur]

		stack = stack[1:]
		for _, child := range children[cur] {
			h[child] = curLvl + 1
			stack = append(stack, child)
		}
	}

	logTree := &logLCA{
		h:        h,
		p:        make([][]int, n),
		children: children,
		parent:   tree, //TODO: this slice should be copied
	}

	logTree.build(0)

	return logTree
}

func (lca *logLCA) build(cur int) {
	n := len(lca.parent)

	for i := 0; i < n; i++ {
		for j := 0; 1<<uint32(j) < n; j++ {
			lca.p[i] = append(lca.p[i], -1)
		}
	}

	for i := 0; i < n; i++ {
		lca.p[i][0] = lca.parent[i]
	}

	for j := 1; 1<<uint32(j) < n; j++ {
		for i := 0; i < n; i++ {
			if lca.p[i][j-1] != -1 {
				lca.p[i][j] = lca.p[lca.p[i][j-1]][j-1] // use dynamic programming
			}
		}
	}
}

func (lca *logLCA) LCA(x, y int) int {
	if lca.h[x] < lca.h[y] { //make sure that x is lower than y for sake of simplicity
		x, y = y, x
	}

	// compute the maximum value `log`, s.t. p[x][log] != -1
	log := -1
	for true {
		if log+1 == len(lca.p[x]) || lca.p[x][log+1] == -1 {
			break
		}
		log++
	}

	// find the ancestor of x which is on the same level as y
	for i := log; i >= 0; i-- {
		if lca.h[x]-(1<<uint32(i)) >= lca.h[y] {
			x = lca.p[x][i]
		}
	}

	// now both x and y are on the same level

	// if x == y then we are at the root
	if x == y {
		return x
	}

	for i := log; i >= 0; i-- {
		if lca.p[x][i] != -1 && lca.p[x][i] != lca.p[y][i] { // we will take maximum possible ancestors of x and y, where these ancestors are different
			x = lca.p[x][i]
			y = lca.p[y][i]
		}
	}
	// once this algorithm has stopped, we are at such maximum ancestors of x and y, such that they are different but they parents are the same
	// therefore the parent is the LCA:

	return lca.parent[x]
}
