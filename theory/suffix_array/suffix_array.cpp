#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <cmath> 

using namespace std;

const int MAX = 1e9;
const int PRIME = 1e9+7;

void powers_of_two(int n, vector<int> &pow){
	int x = 1;
	for(int i = 0; i < n; i++){
		pow.push_back(x);
		x *= 2;
	}
}

struct info{
	int index;
	int first;
	int second;
	info(int index):index(index) {
		first = -1;
		second = -1;
	}
	~info(){ }
};

void suffix_array(vector<int> &SA, vector<vector<int>> &P, const string &x){
	int n = x.length();
	SA.resize(n, -1);
	int nn = static_cast<int>(log2(n-1))+1; //next power of two from length of x
	P.resize(nn+1, vector<int>(n, -1));
	vector<int> pow;
	vector<info> L(n, info(0));
	powers_of_two(nn, pow);
	for(int j = 0; j < n; j++){
		P[0][j] = x[j]-'a';
	}
	auto comp = [](const info &a, const info &b) -> bool{
		return a.first < b.first || (a.first == b.first && a.second <= b.second);
	};
	for(int i = 1; i <= nn; i++){
		for(int j = 0; j < n; j++){
			L[j].index = j;
			L[j].first = P[i-1][j];
			if (j + pow[i-1] < n){
				L[j].second = P[i-1][j+pow[i-1]];
			}
			else L[j].second = -1;
		}
		sort(L.begin(), L.end(), comp);
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
	for(int i = 0; i < n; i++){
		SA[P[nn][i]] = i;
	}
	for(int i = 0; i < n; i++){
		cout << i << " " << (x.substr(SA[i], x.length()-SA[i])) << endl;
	}
}

int main(int argc, char const *argv[])
{
	string x;
	cin >> x;
	vector<int> SA;
	vector<vector<int>> P;
	suffix_array(SA, P, x);
	return 0;
}
