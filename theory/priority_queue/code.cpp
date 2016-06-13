#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

class BinaryHeap
{
public:
	vector<int> a;
	BinaryHeap();
	~BinaryHeap();
	void insert(int x){
		a.push_back(x);
		int i = a.size()-1;
		while(i > 0){
			int parent = getParent(i);
			if (a[parent] < a[i]){
				swap(a[parent], a[i]);
				i = parent;
			}
			else break;
		}
	}
	void pop(){
		swap(a[0], a[a.size()-1]);
		a.pop_back();
		int i = 0;
		while(i < a.size()){
			int left_child = getLeftChild(i);
			int right_child = getRightChild(i);
			int to_swap = i;
			if (left_child < a.size() && a[left_child] > a[to_swap]){
				to_swap = left_child;
			}
			if (right_child < a.size() && a[right_child] > a[to_swap]){
				to_swap = right_child;
			}
			if (to_swap != i){
				swap(a[to_swap], a[i]);
				i = to_swap;
			}
			else {
				break;
			}
		}
	}
	int getParent(int i){
		return ceil((double)i/2)-1;
	}
	int getLeftChild(int i){
		return 2*i+1;
	}
	int getRightChild(int i){
		return 2*i+2;
	}
	int top(){
		return a[0];
	}
	int extractMax(){
		int res = top();
		pop();
		return res;
	}
	void print(){
		for(int i = 0; i < a.size(); i++){
			cout << a[i] << " ";
		}
		cout << endl;
	}
};

BinaryHeap::BinaryHeap(){

}

BinaryHeap::~BinaryHeap(){

}

int main(int argc, char const *argv[])
{
	BinaryHeap heap;	
	heap.insert(1);
	heap.print();
	heap.insert(2);
	heap.print();
	heap.insert(3);
	heap.print();
	heap.insert(5);
	heap.print();
	heap.insert(0);
	heap.print();
	heap.insert(4);
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	heap.pop();
	heap.print();
	return 0;
}
