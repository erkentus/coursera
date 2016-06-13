#include <iomanip>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

#define EPSILON 1e-12

typedef pair<double, double> pdd;

struct cstmcmp
{
    bool operator()(pair<double, double> &a, pair<double, double> &b)
    {
    	double _a = a.first/a.second;
    	double _b = b.first/b.second;
        return _a < _b;
    }
};

int main(int argc, char const *argv[])
{
	int N;
	double cap;
	cin >> N >> cap;
	priority_queue<pdd, vector<pdd>, cstmcmp> items;
	for(int i = 0; i < N; i++){
		double val, weight;
		cin >> val >> weight;
		items.push({val, weight});
	}
	double answer = 0;
	for(int i = 0; i < N; i++){
		if (cap <= EPSILON){
			break;
		}
		pdd cur = items.top();
		items.pop();
		double to_add = min(cur.second, cap);
		answer += to_add*(cur.first/cur.second);
		cap -= to_add;
	}
	cout << setprecision(7) << answer << endl;
	return 0;
}