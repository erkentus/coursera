#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

class DisjointSet{
public:
	DisjointSet();
	DisjointSet(int n);
	~DisjointSet();
	int find(int i){
		if (p[i] == i) return i;
		return p[i] = find(p[i]);
	}
	void unite(int i, int j){
		i = find(i);
		j = find(j);
		if (i == j) return;
		if (rand() % 2 == 0){
			swap(i, j);
		}
		p[i] = j;
		size[j] += size[i];
		size[i] = 0;
	}
private:
	vector<int> p;
	vector<int> size;
};
