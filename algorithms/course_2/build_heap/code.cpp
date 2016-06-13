#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

class HeapSort
{
private:
	vector<int> *a;
	vector<pair<int,int>> swaps;
	int size;
public:
	HeapSort(vector<int> *t);
	~HeapSort();
	void sort(){
		buildHeap();
		// don't sort lol
		// int repeat = size;
		// for(int i = 0; i < repeat-1; i++){
		// 	swap((*a)[0], (*a)[size-1]);
		// 	size--;
		// 	siftDown(0);
		// }
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
			if (l < size && (*a)[l] < (*a)[to_swap]){
				to_swap = l;
			}
			if (r < size && (*a)[r] < (*a)[to_swap]){
				to_swap = r;
			}
			if (to_swap != i){
				swaps.push_back({i, to_swap});
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
	void print_result(){
		cout << swaps.size() << endl;
		for(int i = 0; i < swaps.size(); i++){
			cout << swaps[i].first << " " << swaps[i].second << endl;
		}
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
	int n;
	cin >> n;
	vector<int> arr(n);
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		arr[i] = x;
	}
	HeapSort h(&arr);
	h.sort();
	h.print_result();
	return 0;
}
