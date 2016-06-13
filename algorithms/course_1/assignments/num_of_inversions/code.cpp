#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

long long count_merge_sort(vector<int> &a,int l,int r){
	vector<int> res(r-l+1);
	if (l >= r){
		return 0;
	}
	long long total = 0;
	int mid = (l+r)/2;
	total += count_merge_sort(a, l, mid);
	total += count_merge_sort(a, mid+1, r);
	int lp = l;
	int rp = mid+1;
	int index = 0;
	int count_r = 0;
	while(true){
		if (lp == (mid+1) && rp == (r+1)){
			break;
		}
		else if (lp == mid+1){
			res[index] = a[rp];
			count_r++;
			rp++;
		}
		else if (rp == r+1){
			res[index] = a[lp];
			lp++;
			total+=count_r;
		}
		else {	
			if (a[lp] > a[rp]){
				res[index] = a[rp];
				count_r++;
				rp++;
			}
			else {
				res[index] = a[lp];
				total+= count_r;
				lp++;
			}
		}
		index++;
	}
	for(int i = l; i < r+1; i++){
		a[i] = res[i-l];
	}
	return total;
}

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	vector<int> a(N);
	for(int i = 0; i < N; i++){
		int x;
		cin >> x;
		a[i] = x;
	}
	cout << count_merge_sort(a, 0, a.size()-1) << endl;
	/* code */
	return 0;
}
