#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
	unordered_map<int, string> m;
	int N;
	cin >> N;
	for(int i = 0; i < N; i++){
		string type;
		cin >> type;
		if (type == "add"){
			int val;
			string name;
			cin >> val >> name;
			m[val] = name;
		}
		if (type == "find"){
			int val;
			cin >> val;						
			if (m.find(val) != m.end()){
				cout << m[val] << endl;
			}
			else {
				cout << "not found" << endl;
			}
		}
		if (type == "del"){
			int val;
			cin >> val;
			m.erase(val);
		}
	}
	return 0;
}
