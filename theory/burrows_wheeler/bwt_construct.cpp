#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
/**
 * create a bwt matrix and bwt string by dumb sorting and creating all rotations
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[])
{
	string x;
	cin >> x;
	vector<string> bwt;
	for(int i = 0; i < x.length(); i++){
		string y;
		if (i > 0) y = x.substr(i, x.length()-i) + x.substr(0, i);
		else y = x;
		bwt.push_back(y);
	}
	sort(bwt.begin(), bwt.end());
	string bwt_string(x.length(), ' ');
	for(int i = 0; i < x.length(); i++){
		bwt_string[i] = bwt[i][x.length()-1];
	}
	cout << bwt_string << endl;
	return 0;
}
