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
	double weight;
	edge(int from, int to, double weight): from(from), to(to), weight(weight) { };
};

struct point{ 
	int x;
	int y;
	point(int x, int y): x(x), y(y){ };
};

double dist(point *p1, point *p2){
	int x1 = p1->x;
	int x2 = p2->x;
	int y1 = p1->y;
	int y2 = p2->y;
	double dx = (double)x1 - (double)x2;
	double dy = (double)y1 - (double)y2;
	return sqrt(dx*dx+dy*dy);
}

int main(int argc, char const *argv[])
{
	ios::sync_with_stdio(false);
	vector<edge*> edges;
	vector<point*> points;
	int n;
	cin >> n;
	DisjointSet s(n);
	for(int i = 0; i < n; i++){
		int x, y;
		cin >> x >> y;
		point *p = new point(x,y);
		points.push_back(p);
	}
	for(int i = 0; i < n; i++){
		double min = (double)1e12;
		for(int j = i + 1; j < n; j++){
			double d = dist(points[i], points[j]);
			edge *e = new edge(i, j, d);
			edges.push_back(e);
		}
	}
	sort(edges.begin(), edges.end(), [](const edge* a, const edge* b) -> bool {
		return a->weight < b->weight;
	});
	double total = 0;
	for(auto it = edges.begin(); it != edges.end(); it++){
		edge *e = *it;
		int from = e->from;
		int to = e->to;
		if (s.find(from) != s.find(to)){
			total += e->weight;
			s.unite(from, to);
		}
	}
	cout << setprecision(12) << total << endl;
	/* code */
	return 0;
}
