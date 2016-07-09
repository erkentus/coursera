#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <assert.h>

using namespace std;


typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;

const ll MAX = 1e15;

void floyd_warshall(const vector<vector<pii>> &graph, vector<vector<ll>> &floyd){
	int n = graph.size();
	assert(n > 1);
	assert(floyd.size() == n);
	assert(floyd[0].size() == n);
	for(int i = 0; i < n; i++){
		floyd[i][i] = 0ll;
		for(int j = 0; j < graph[i].size(); j++){
			int from = i;
			int to = graph[i][j].first;
			int weight = graph[i][j].second;
			floyd[from][to] = static_cast<ll>(weight);
		}
	}
	for(int k = 0; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if (floyd[i][j] > floyd[i][k] + floyd[k][j]){
					floyd[i][j] = floyd[i][k] + floyd[k][j];
				}
			}
		}
	}	
}

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	vector<vector<pii>> graph(n);
	for(int i = 0; i < m; i++){
		int x,y,w;
		cin >> x >> y >> w;
		graph[x-1].push_back({y-1, w});
	}
	vector<vector<ll>> floyd(n, vector<ll>(n, MAX));
	floyd_warshall(graph, floyd);
	/** queries follow */
	int q;
	cin >> q;
	for(int i = 0; i < q; i++){
		int x,y;
		cin >> x >> y;
		if (floyd[x-1][y-1] < MAX)cout << floyd[x-1][y-1] << endl;
		else cout << -1 << endl;
	}
	return 0;
}
