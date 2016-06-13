#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

typedef pair<long long, long long> pii;

struct pair_compare_reverse
{
    bool operator()(pair<long long, long long> &a, pair<long long, long long> b)
    {
        return a.first > b.first || a.first == b.first && a.second > b.second;
    }
};

int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	priority_queue<pii, vector<pii>, pair_compare_reverse> q;
	for(long i = 0; i < n; i++){
		q.push({0, i});
	}
	for(int i = 0; i < m; i++){
		long long x;
		cin >> x;
		pii to_work = q.top();
		cout << q.top().second << " " << (q.top().first) << endl;
		q.pop();
		q.push({(to_work.first+x), to_work.second});
	}

	return 0;
}
