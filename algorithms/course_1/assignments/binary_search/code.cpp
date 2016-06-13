#include <iostream>
#include <vector>

using namespace std;

int binary_search(int l, int r, int x, vector<int> &arr){
	if (l == r){
		return l;
	}
	int cand = (l+r)/2;
	if (arr[cand] < x){
		return binary_search(cand+1, r, x, arr);
	}
	else if (arr[cand] == x){
		return cand;
	}
	else{
		return binary_search(l, cand, x, arr);
	}
}

int solution(int x, vector<int> &arr){
	int l = binary_search(0, arr.size()-1, x, arr);
	if (arr[l] == x){
		return l;
	}
	return -1;
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
	int K;
	cin >> K;
	for(int i = 0; i < K; i++){
		int x;
		cin >> x;
		cout << solution(x, arr) << " ";
	}
	cout << endl;
	return 0;
}
