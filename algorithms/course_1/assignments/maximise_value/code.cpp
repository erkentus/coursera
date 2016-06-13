#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	string x;
	cin >> x;
	vector<int> num;
	vector<char> ops;
	for(int i = 0; i < x.length(); i++){
		if (i % 2 == 0){
			num.push_back(x[i]-'0');
		}
		else {
			ops.push_back(x[i]);
		}
	}
	vector<vector<long long> > M(ops.size()+1, vector<long long>(ops.size()+1, 0));
	vector<vector<long long> > m(ops.size()+1, vector<long long>(ops.size()+1, 0));
	for(int delta = 0; delta < ops.size()+1; delta++){
		for(int start = 0; start < ops.size()-delta+1; start++){
			if (delta == 0){
				M[start][start+delta] = num[start];
				m[start][start+delta] = num[start];
			}
			else{
				vector<long long> interim;
				for(int k = 0; k < delta; k++){
					if (ops[start+k] == '-'){
						interim.push_back(m[start][start+k]-M[start+k+1][start+delta]);
						interim.push_back(M[start][start+k]-m[start+k+1][start+delta]);
						interim.push_back(m[start][start+k]-m[start+k+1][start+delta]);
						interim.push_back(M[start][start+k]-M[start+k+1][start+delta]);
					}
					if (ops[start+k] == '+'){
						interim.push_back(m[start][start+k]+m[start+k+1][start+delta]);
						interim.push_back(M[start][start+k]+M[start+k+1][start+delta]);
						interim.push_back(m[start][start+k]+M[start+k+1][start+delta]);
						interim.push_back(M[start][start+k]+m[start+k+1][start+delta]);
					}
					if (ops[start+k] == '*'){
						interim.push_back(m[start][start+k]*m[start+k+1][start+delta]);
						interim.push_back(M[start][start+k]*M[start+k+1][start+delta]);
						interim.push_back(m[start][start+k]*M[start+k+1][start+delta]);
						interim.push_back(M[start][start+k]*m[start+k+1][start+delta]);
					}
				}
				M[start][start+delta] = *max_element(interim.begin(), interim.end());
				m[start][start+delta] = *min_element(interim.begin(), interim.end());
			}
		}
	}
	cout << M[0][ops.size()] << endl;
	return 0;
}
