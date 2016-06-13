#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	long long N;
	cin >> N;
	int sN = floor(sqrt(2*N));
	if (sN*(sN+1) > 2*N){
		sN--;
	}
	cout << sN << endl;
	for(int i = 1; i < sN; i++){
		cout << i << " ";
	}
	cout << sN + (N-sN*(sN+1)/2);
	cout << endl;		
	return 0;
}
