#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	int buffer, N;
	cin >> buffer >> N;
	vector<pair<int,int>> packets;
	for(int i = 0; i < N; i++){
		int arr, pro;
		cin >> arr >> pro;
		packets.push_back({arr, pro});
	}	

	queue<int> in_progress; 
	vector<int> timings(N);
	int t = 0;
	int time_so_far = 0;
	for(int i = 0; i < N; i++){
		pair<int, int> to_process = packets[i];
		int arr = to_process.first;
		while(true){
			if (in_progress.empty()) break;
			pair<int, int> next_process = packets[in_progress.front()];
			if (next_process.first > time_so_far){
				time_so_far = next_process.first;
			}
			if (time_so_far + next_process.second > arr){
				break;
			}
			else {
				buffer++;
				timings[in_progress.front()] = time_so_far;
				time_so_far += next_process.second;
				in_progress.pop();
			}
		}
		if (buffer == 0){
			timings[i] = -1;
		}
		else {
			buffer--;
			in_progress.push(i);
		}
	}
	while(true){
		if (in_progress.empty()) break;
		pair<int, int> next_process = packets[in_progress.front()];
		if (next_process.first > time_so_far){
			time_so_far = next_process.first;
		}
		timings[in_progress.front()] = time_so_far;
		time_so_far += next_process.second;
		in_progress.pop();
	}
	for(int i = 0; i < N; i++){
		cout << timings[i] << endl;
	}
	return 0;
}
