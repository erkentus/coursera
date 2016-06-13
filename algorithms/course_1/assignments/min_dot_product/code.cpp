#include <vector>
#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	priority_queue<int> A;
	priority_queue<int, vector<int>, greater<int> > B;
	for(int i = 0; i < N; i++){
		int a;
		cin >> a;
		A.push(a);
	}
	for(int i = 0; i < N; i++){
		int b;
		cin >> b;
		B.push(b);
	}
	long long result = 0;
	for(int i = 0; i < N; i++){
		long long a,b;
		a = A.top();
		A.pop();
		b = B.top();
		B.pop();
		result += a*b;
	}	
	cout << result << endl;
	return 0;
}
