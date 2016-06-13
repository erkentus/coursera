#include <iostream>

using namespace std;

long long gcd(long long a, long long b){
	if (a == 0 || b == 0){
		return a+b;
	}
	if (a == b){
		return a;
	}	
	if (a > b){
		return gcd(a%b, b);
	}
	else{
		return gcd(a, b%a);
	}
}

int main(int argc, char const *argv[])
{
	long long a, b;
	cin >> a >> b;
	long long answer = gcd(a,b);
	cout << answer << endl;
	return 0;
}