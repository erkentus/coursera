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
		if (rand() % 2 == 0){
			swap(i, j);
		}
		p[i] = j;
	}
private:
	vector<int> p;
};

DisjointSet::DisjointSet(int n){
	for(int i = 0; i < n; i++){
		p.push_back(i);
	}
};
DisjointSet::~DisjointSet(){};

struct edge{
	int from;
	int to;
	int weight;
	edge(int from, int to, int weight): from(from), to(to), weight(weight) { };
};


int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	vector<edge*> edges;
	int n, m;
	cin >> n >> m;
	DisjointSet s(n);
	for(int i = 0; i < m; i++){
		int x, y, w;
		cin >> x >> y >> w;
		edge *e = new edge(x-1,y-1,w);
		edges.push_back(e);
	}
	sort(edges.begin(), edges.end(), [](const edge* a, const edge* b) -> bool {
		return a->weight < b->weight;
	});
	ll total = 0;
	for(auto it = edges.begin(); it != edges.end(); it++){
		edge *e = *it;
		int from = e->from;
		int to = e->to;
		if (s.find(from) != s.find(to)){
			total += e->weight;
			s.unite(from, to);
		}
	}
	cout << total << endl;
	/* code */
	return 0;
}
