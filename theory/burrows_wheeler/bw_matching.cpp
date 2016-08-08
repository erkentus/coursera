#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct t{
	int l_index; //index in bwt string
	int f_index; //index in suffix array
	t(int f_index): f_index(f_index) {};
};

inline int con(char x){
	if (x == '$') return 0;
	if (x == 'A') return 1;
	if (x == 'C') return 2;
	if (x == 'G') return 3;
	if (x == 'T') return 4;
	return -1;
}

int bw_matching(
	const string &x, 
	const string &y, 
	const vector<int> &last_to_first, 
	const string &p,
	const vector<vector<int>> &count,
	const vector<int> &first
	)
{
	int n = x.length();
	int m = p.length();
	int cur_match = m - 1;
	int l = 0;
	int r = n - 1;
	while(l <= r){
		if (cur_match == -1) break;
		char chr = p[cur_match];
		int ind = con(chr);
		int f_ind = first[ind];
		if (f_ind == -1) return 0;
		if (l > 0) l = f_ind + count[ind][l-1];
		else l = f_ind;
		r = f_ind + count[ind][r]-1;
		cur_match--;
	}
	return r - l + 1;
}

int main(int argc, char const *argv[])
{
	string x;
	cin >> x;
	string y = x;
	sort(y.begin(), y.end());
	vector<int> last_to_first(x.length(), -1);
	vector<vector<t>> c(5);
	vector<int> _c(5, 0);
	vector<vector<int>> count(5, vector<int>(x.length(), 0));
	vector<int> first(5, -1);
	for(int i = 0; i < y.length(); i++){
		char chr = y[i];
		int ind = con(chr);
		if (first[ind] == -1) first[ind] = i;
		c[ind].push_back(t(i));
	}
	for(int i = 0; i < x.length(); i++){
		char chr = x[i];
		int ind = con(chr);
		for(int j = 0; j < 5; j++){
			if (j == ind) count[j][i] = (i == 0) ? 1: count[j][i-1]+1;
			else count[j][i] = (i == 0) ? 0: count[j][i-1];
		}
		last_to_first[i] = c[ind][_c[ind]].f_index;
		c[ind][_c[ind]].l_index = i;
		_c[ind]++;
	}
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		string p;
		cin >> p;
		int occ = bw_matching(x, y, last_to_first, p, count, first);
		cout << occ << " ";
	}
	cout << endl;
	return 0;
}
