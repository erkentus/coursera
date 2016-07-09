#include <iostream>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<double, int> pdi;
typedef pair<ll, ll> pll;

const double MAX = static_cast<double>(1e10);

namespace util {
	template<class T> 
	inline double dist(T x1, T x2, T y1, T y2){
		double dx = static_cast<double>(x1-x2);
		double dy = static_cast<double>(y1-y2);
		return sqrt(dx*dx + dy*dy);
	} 
}

template<class T>
struct point{
	T x;
	T y;
	point(T x, T y): x(x), y(y) {};
	~point() {};
	static double dist(const point<T> *p1,const point<T> *p2){
		return util::dist(p1->x, p2->x, p1->y, p2->y);
	}
};
/** very similar to Dijkstra algorithm */
double prim(const vector<point<int>*> &points){
	int n = points.size();
	vector<double> cost(n, MAX); //track cost of adding a new edge
	vector<bool> added(n, false);
	int start = 0;
	auto comp = [](const pdi &a, const pdi &b) -> bool {
		return a.first > b.first;
	};
	priority_queue<pdi, vector<pdi>, decltype(comp)> q(comp);
	q.push({0.0, start});
	cost[start] = 0.0;
	parent[0] = 0;
	double mst = 0.0;
	int num_vert = 0;
	while(!q.empty() && num_vert < n){
		pdi cur = q.top();
		double cur_cost = cur.first;
		int cur_ver = cur.second;
		point<int> *cur_point = points[cur_ver];
		q.pop();
		if (added[cur_ver]) continue;
		added[cur_ver] = true;
		num_vert++;
		mst += cur_cost;// compute the distance;
		for(int i = 0; i < n; i++){
			if (!added[i]) {
				point<int> *next_point = points[i];
				double d = point<int>::dist(cur_point, next_point);
				if (cost[i] > d) {
					cost[i] = d;
					q.push({cost[i], i});
				}
			}
		}
	}
	return mst;
}

int main(int argc, char const *argv[])
{
	/** use Prim algo to determine MST for a given set of points on the plane with weight equal to  
	dist between points */
	// point<int> *p1 = new point<int>(0,0);
	// point<int> *p2 = new point<int>(1,1);
	int n;
	cin >> n;
	vector<point<int>*> points;
	for(int i = 0; i < n; i++){
		int x,y;
		cin >> x >> y;
		points.push_back(new point<int>(x,y));
	}
	cout << setprecision(12) << prim(points) << endl;
	return 0;
}
