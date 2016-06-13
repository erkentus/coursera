#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	vector<long long> interm(N+1);
	if (N == 1) {
		cout << 0 << endl;
		cout << 1 << endl;
		return 0;
	}
	for(int i = 1; i < N+1; i++){
		if (i == 1){
			interm[1] = 0;
		}
		else {
			vector<long long> vals;
			vals.push_back(interm[i-1]);
			if (i % 3 == 0){
				vals.push_back(interm[i/3]);
			}
			if (i % 2 == 0){
				vals.push_back(interm[i/2]);
			}
			interm[i] = *min_element(vals.begin(), vals.end()) + 1;
		}
	}
	cout << interm[N] << endl;
	stack<int> path;
	int cur = N;
	while(true){
		int next = cur-1;
		if (cur % 2 == 0 && interm[cur/3] <= interm[next]){
			next = cur/2;
		}
		if (cur % 3 == 0 && interm[cur/3] <= interm[next]){
			next = cur/3;
		}
		path.push(next);
		cur = next;
		if (next == 1) break;
	}
	while(!path.empty()){
		cout << path.top() << " ";
		path.pop();
	}
	cout << N << endl;
	return 0;
}
