#include <iostream>

using namespace std;

int fib(int n){
	int prev = 0;
	int cur = 1;
	int next;
	for(int i = 0; i < n-1; i++){
		next = prev + cur;
		prev = cur;
		cur = next % 10;
	}
	return cur;
}

int main(int argc, char const *argv[])
{
	int size;
	cin >> size;
	int answer = fib(size);
	cout << answer << endl;
	return 0;
}