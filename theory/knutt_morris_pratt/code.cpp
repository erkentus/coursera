#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

/**
 * return prefix fn, j = s[i], where j is the largest number, s.t. j <= i
 * x[0..j-1] == x[j-i+1..i] and j < i;
 */
vector<int> prefix_fn(const string &p){
	vector<int> s(p.length(), 0);
	int n = p.length();
	int border = 0;
	s[0] = 0;
	for(int i = 1; i < n; i++){
		while(border > 0 && p[i] != p[border]){
			border = s[border-1];
		}
		if (p[i] == p[border]){
			border = border+1;
		}
		else {
			border = 0;
		}
		s[i] = border;
	}
	return s;
}
/**
 * kmp algo
 */
void print_match(const string &text, const string &pattern){
	string S =  pattern + '$' + text;
	vector<int> pfn = prefix_fn(S);
	for(int i = pattern.length() + 1; i < S.length(); i++){
		if (pfn[i] == pattern.length()){
			cout << i - 2*pattern.length() << " "; //starting point in text
		}
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
	string p,t;
	cin >> p >> t;
	print_match(t, p);
	return 0;
}
