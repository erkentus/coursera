#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	int N;
	cin >> N;
	int _10 = N/10;
	int _5 = (N-(_10*10))/5;
	int _1 = (N-(_10*10+_5*5));
	cout << (_10 + _5 + _1) << endl;
	return 0;
}