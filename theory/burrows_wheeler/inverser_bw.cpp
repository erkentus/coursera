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

int main(int argc, char const *argv[])
{
	string x;
	cin >> x;
	string y = x;
	sort(y.begin(), y.end());
	vector<int> first_to_last(x.length(), -1);
	vector<vector<t>> c(5);
	vector<int> _c(5, 0);
	for(int i = 0; i < y.length(); i++){
		int chr = y[i];
		int ind = con(chr);
		c[ind].push_back(t(i));
	}
	for(int i = 0; i < x.length(); i++){
		char chr = x[i];
		int ind = con(chr);
		first_to_last[c[ind][_c[ind]].f_index] = i;
		c[ind][_c[ind]].l_index = i;
		_c[ind]++;
	}
	string orig(x.length(), ' '); //original string
	int next = c[0][0].l_index; //this is the pointer to position in x of '$'
	int len = 0;
	while(len < x.length()){
		char cor = y[next];
		orig[len] = cor;
		next = first_to_last[next];
		len++;
	}
	cout << orig << endl;
	return 0;
}
