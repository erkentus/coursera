#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

#define MAX 1e7

typedef pair<int, int> pii;

int main(int argc, char const *argv[])
{
	int s,p;
	cin >> s >> p;
	vector<pii> arr;
	vector<int> answers(p);
	for(int i = 0; i < s; i++){
		int x;
		cin >> x;
		arr.push_back({x, 0});
		int y;
		cin >> y;
		arr.push_back({y, MAX});
	}
	for(int i = 0; i < p; i++){
		int p;
		cin >> p;
		arr.push_back({p, i+1});
	}
	sort(arr.begin(), arr.end());
	int cur = 0;
	for(int i = 0; i < arr.size(); i++){
		if (arr[i].second == 0){
			cur++;
		}	
		if (arr[i].second == MAX){
			cur--;
		}	
		else if (arr[i].second >= 1){
			answers[arr[i].second-1] = cur;
		}
	}
	for(int i = 0; i < p; i++){
		cout << answers[i] << " ";		
	}
	cout << endl;
	return 0;
}
