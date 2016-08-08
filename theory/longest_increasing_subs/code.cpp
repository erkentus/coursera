#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

int binary_search(int l, int r, const vector<int> &d, const vector<int> &a, int x){
	if (l >= r) {
		if (d[l] < x) return l;
		return l-1;
	};
	int cand = (l+r)/2;
	if (d[cand] >= x) return binary_search(l, cand-1, d, a, x);
	if (d[cand] < x && (d[cand+1] >= x || d[cand+1] == -1)) return cand;
	else {
		return binary_search(cand+1, r, d, a, x);
	}
}
/**
 * seq will store the actual longest increasing function
 * the function will return the length of it
 * @param  a   [description]
 * @param  seq [description]
 * @return     [description]
 */
int LIS(const vector<int> &a, vector<int> &seq){
	int curMaxLen = 0;
	int n = a.size();
	vector<int> t(n, -1);
	//t[i]=j points to the index in a[], j, s.t. among all LIS of length i ending at x, a[j] is minimum among all such x
	vector<int> d(n, -1); //d is strictly increasing array to perform binary search, basically d[i] = a[t[i]]
	vector<int> prev(n, -1);
	for(int i = 0; i < n; i++){
		if (i == 0) {
			t[0] = 0; 
			d[curMaxLen] = a[0];
			curMaxLen = 1;	
			continue;
		}
		/** replace the following with binary search */
		int j = binary_search(0, curMaxLen-1, d, a, a[i]);
		if (j == curMaxLen-1) 
		{
			curMaxLen++;
		}
		if (t[j+1] == -1 || a[t[j+1]] > a[i]) {
			d[j+1] = a[i];
			t[j+1] = i;
			if (j >= 0) prev[i] = t[j]; //this is to backtrack after we found the length
		}
		/** end of replace */
	}
	/** now let's construct the actual sequence */
	int cur = t[curMaxLen-1];
	while(cur != -1){
		seq.push_back(a[cur]);
		cur = prev[cur];
	}
	return curMaxLen;	
}

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<pii> in;
	vector<int> a;
	for(int i = 0; i < n; i++){
		int x,y;
		cin >> x >> y;
		in.push_back(make_pair(x,y));
	}
	sort(in.begin(), in.end());
	for(int i = 0; i < in.size(); i++){
		cout << in[i].first << " " << in[i].second << endl;
		if (i > 0 && in[i].first == in[i-1].first)
			a.pop_back();
		a.push_back(in[i].second);
	}
	// int n;
	// cin >> n;
	// vector<int> a(n);
	vector<int> seq;
	// for(int i = 0; i < n; i++){
	// 	cin >> a[i];
	// }
	cout << "LIS length: " << LIS(a, seq) << endl;
	cout << "Here is the actual LIS (from bigger to smaller)" << endl;
	for(int i = 0; i < seq.size(); i++){
		cout << seq[i] << " ";
	}
	// cout << endl;
	return 0;
}