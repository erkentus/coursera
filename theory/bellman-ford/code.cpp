#define MAX (int)1e9
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef long long ll;

struct edge{
	int from;
	int to;
	int weight;
	edge(int from, int to, int weight):from(from), to(to), weight(weight) {}
};

bool bellman_ford(const vector<edge*> &edges, vector<int> &min_dist, int from){
	int num_vert = min_dist.size();
	min_dist[from] = 0;
	int total_iter = 0;
	for(int i = 0; i < num_vert-1; i++){
		bool relaxed = false;
		total_iter++;
		for(int j = 0; j < edges.size(); j++){
			edge *e = edges[j];
			int from = e->from;
			int to = e->to;
			int weight = e->weight;
			if (min_dist[to] > min_dist[from] + weight){
				relaxed = true;
				min_dist[to] = min_dist[from] + weight;
			}
		}
		if (!relaxed) break;
	}
	if (total_iter < num_vert-1) return false;
	bool check_negative = false;
	for(int j = 0; j < edges.size(); j++){
		edge *e = edges[j];
		int from = e->from;
		int to = e->to;
		int weight = e->weight;
		if (min_dist[to] > min_dist[from] + weight){
			check_negative = true;
			min_dist[to] = min_dist[from] + weight;
		}
	}
	return check_negative;
}

int main(int argc, char const *argv[])
{
	int n, m;
	vector<edge*> edges;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a,b,c;
		cin >> a >> b >> c;
		edge *e = new edge(a-1,b-1,c);
		edges.push_back(e);
	}
	vector<int> min_dist(n, MAX);
	cout << bellman_ford(edges, min_dist, 0) << endl;
	return 0;
}