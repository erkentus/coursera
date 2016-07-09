#include <algorithm>
#include <iostream>
#include <set>
#include <stack> 
#include <vector>

using namespace std;

bool find_path(int start, int end, vector<vector<int> > &edges){
	set<int> visited;
	stack<int> to_visit;
	bool found = false;
	to_visit.push(start);
	while(!to_visit.empty()){
		int cur = to_visit.top();
		if (cur == end){
			found = true;
			break;
		}
		to_visit.pop();
		for(auto it = edges[cur].begin(); it != edges[cur].end(); it++){
			if (visited.find(*it) == visited.end()){
				visited.insert(*it);
				to_visit.push(*it);
			}
		}
	}
	return found;
}

int main(int argc, char const *argv[])
{
	int n,m;
	cin >> n >> m;
	vector<vector<int> > edges(n);
	for(int i = 0; i < m; i++){
		int a,b;
		cin >> a >> b;
		edges[a-1].push_back(b-1);
		edges[b-1].push_back(a-1);
	}
	int start;
	int end;
	cin >> start >> end;
	cout << find_path(start-1, end-1, edges) << endl;
	return 0;
}
