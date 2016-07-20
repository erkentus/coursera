#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <cmath> 

using namespace std;

const int MAX = 1e9;
const int PRIME = 1e9+7;
typedef long long ll;
void powers_of_two(int n, vector<int> &t){
	int x = 1;
	for(int i = 0; i < n; i++){
		t.push_back(x);
		x *= 2;
	}
}

struct _tuple{
	int index;
	int first;
	int second;
	_tuple(int index):index(index) {
		first = -1;
		second = -1;
	}
	~_tuple(){ }
};
/**
 *	longest common prefix of two suffixes starting at indexes i and j
 *	P is defined as in suffix_array
 * 	x initial string
 */

const int d = 22;

vector<int> powers;



int LCP(int i, int j, vector<vector<int>> &P, const string &x){
	int n = x.length();
	if (i == j) return n-i;
	// if (n == 1) return 0;
	int nn = static_cast<int>(floor(log2(n)))+1; //next power of two from length of x
	int total = 0;
	for(int step = nn; step >= 0; step--){
		if (i >= n || j >= n) break;
		if (P[step][i] == P[step][j]){
			total += powers[step];
			i += powers[step];
			j += powers[step];
		}
	}
	return total;	
}

/**
 * @param P  preliminary result P[i][j] is the rank of suffix at index "j" as compared using first 2^i characters
 * @param x  actual string
 */
void suffix_array(vector<vector<int>> &P, const string &x){
	int n = x.length();
	int nn = static_cast<int>(floor(log2(n)))+1 ; //next power of two from length of x
	P.resize(nn+1, vector<int>(n, -1));
	if (n == 1) {
		P[0][0] = 0;
		return;
	}
	vector<_tuple> L(n, _tuple(0));
	for(int j = 0; j < n; j++){
		P[0][j] = x[j]-'a';
	}
	for(int i = 1; i <= nn; i++){
		for(int j = 0; j < n; j++){
			L[j].index = j;
			L[j].first = P[i-1][j];
			if (j + powers[i-1] < n){
				L[j].second = P[i-1][j+powers[i-1]];
			}
			else L[j].second = -1;
		}
		sort(L.begin(), L.end(), [](const _tuple &a, const _tuple &b){
			return a.first < b.first || (a.first == b.first && a.second < b.second);
		});
		for(int j = 0; j < n; j++){
			if (j == 0){
				P[i][L[j].index] = 0;
			}
			else {
				if (L[j].first == L[j-1].first && L[j].second == L[j-1].second){
					P[i][L[j].index] = P[i][L[j-1].index];
				} else {
					P[i][L[j].index] = j;
				}
			}
		}
	}
}


int main(int argc, char const *argv[])
{
	powers_of_two(d, powers);
	string x, orig;
	cin >> x;
	orig = x;
	reverse(x.begin(), x.end());
	vector<vector<int>> P;
	suffix_array(P, x);
	int ans = 0;
	for(int i = 1; i < x.length(); i++){
		if (LCP(0, i, P, x) >= i) ans = i;
	}
	cout << orig.substr(orig.length()-ans, ans) << endl;
	return 0;
}
