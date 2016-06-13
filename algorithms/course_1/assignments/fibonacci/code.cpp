#include <iostream>

using namespace std;

int fib(int n){
	int cur = 0;
	int next = 1;
	int tmp;
	for(int i = 0; i < n; i++){
		tmp = next + cur;
		cur = next;
		next = tmp;
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