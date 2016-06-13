#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	vector<int> numbers(N);
	for(int i = 0; i < N; i++){
		int x;
		cin >> x;
		numbers[i] = x;
	}
	sort(numbers.begin(), numbers.end());
	int exist = 0;
	int half = N/2;
	int i = 0;
	while(i + half < N){
		if (numbers[i] == numbers[i+half]){
			exist = 1;
			break;
		}
		i++;
	}
	cout << exist << endl;
	return 0;
}
