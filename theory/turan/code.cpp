#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

typedef long long ll;

/** upper bound on the number of edges a graph with N vertices can have if does not have clique of size M */
int turan(int n, int m){
	double coff = (1 - 1/(static_cast<double>(m-1))) * static_cast<double>(n) * static_cast<double>(n)/2;		
	return floor(coff);
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	cout << turan(23,3) << endl;
	return 0;
}
