#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

class HeapSort
{
private:
	vector<int> *a;
	int size;
public:
	HeapSort(vector<int> *t);
	~HeapSort();
	void sort(){
		buildHeap();
		int repeat = size;
		for(int i = 0; i < repeat-1; i++){
			swap((*a)[0], (*a)[size-1]);
			size--;
			siftDown(0);
		}
	}
	void buildHeap(){
		for(int i = ceil((double)size/2); i > -1; i--){
			siftDown(i);
		}
	}
	void siftDown(int i){
		while(i < size){
			int l = getLeftChild(i);
			int r = getRightChild(i);
			int to_swap = i;
			if (l < size && (*a)[l] > (*a)[to_swap]){
				to_swap = l;
			}
			if (r < size && (*a)[r] > (*a)[to_swap]){
				to_swap = r;
			}
			if (to_swap != i){
				swap((*a)[to_swap], (*a)[i]);
				i = to_swap;
			}
			else break;
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
};

HeapSort::HeapSort(vector<int> *t){
	a = t;
	size = (*t).size();
}

HeapSort::~HeapSort(){

}

int main(int argc, char const *argv[])
{
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(10);
	arr.push_back(-10);
	arr.push_back(2);
	arr.push_back(6);
	arr.push_back(9);
	arr.push_back(18);
	HeapSort h(&arr);
	h.sort();
	for(int i = 0; i < arr.size(); i++){
		cout << arr[i] << endl;
	}
	return 0;
}
