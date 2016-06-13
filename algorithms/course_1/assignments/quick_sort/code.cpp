#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> pii;

pii partition(vector<int> &arr, int l, int r){
	int x = arr[l];
	int j = l;
	for(int i = l + 1; i <= r; i++){
		if (arr[i] < x){
			j++;
			swap(arr[i],arr[j]);
		}
	}
	swap(arr[l], arr[j]);
	int k = j;
	while(true){
		if (arr[k+1] == arr[j]) k++;
		else break;
	}
	return {j, k};	
}

void quick_sort(vector<int> &arr, int l, int r){
	if (l >= r){
		return;
	}
	int k = l + rand() % (r - l + 1);
	swap(arr[l], arr[k]);
	pii pts = partition(arr, l, r);
	quick_sort(arr, l, pts.first-1);
	quick_sort(arr, pts.second+1, r);
}

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	vector<int> arr(N);
	for(int i = 0; i < N; i++){
		int x;
		cin >> x;
		arr[i] = x;
	}
	quick_sort(arr, 0, arr.size()-1);
	for(int i = 0; i < N; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
	/* code */
	return 0;
}