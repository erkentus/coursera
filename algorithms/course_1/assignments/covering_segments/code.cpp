#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int main()
{
	int N;
	cin >> N;
	priority_queue<pii, vector<pii>, greater<pii> > segments;
	for(int i = 0; i < N; i++){
		int _s, _e;
		cin >> _s >> _e;
		segments.push({_s, _e});
	}	

	vector<int> chosen_points;
	while(true){
		if (segments.size() == 0) {
			break;
		}
		pii cur_seg = segments.top();
		segments.pop();
		if (segments.size() == 0){
			chosen_points.push_back(cur_seg.first);
			break;
		}
		while(true){
			if (segments.size() == 0) break;
			pii next_seg = segments.top();
			if (next_seg.second >= cur_seg.second && next_seg.first <= cur_seg.second){
				segments.pop();
			}
			else if (next_seg.second <= cur_seg.second){
				cur_seg.first = next_seg.first;
				cur_seg.second = next_seg.second;
			}
			else break;
		}
		chosen_points.push_back(cur_seg.second);
	}	
	cout << chosen_points.size() << endl;
	for(int i = 0; i < chosen_points.size(); i++){
		cout << chosen_points[i] << " ";
	}
	cout << endl;
	return 0;
}