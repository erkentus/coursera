#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

struct brk {
	char type;
	int pos;
};

int main(int argc, char const *argv[])
{
	string s;
	int err = -1;
	cin >> s;
	stack<brk> brackets;
	for(int i = 0; i < s.size(); i++){
		if (s[i] == '(' || s[i] == '[' || s[i] == '{'){
			brk n;
			n.type = s[i];
			n.pos = i;
			brackets.push(n);
		}
		else if (s[i] == ')'){
			if (brackets.empty()){
				err = i;
				break;
			}
			brk e = brackets.top();
			if (e.type != '('){
				err = i;
				break;
			}
			else{ 
				brackets.pop();
			}
		}
		else if (s[i] == ']'){
			if (brackets.empty()){
				err = i;
				break;
			}
			brk e = brackets.top();
			if (e.type != '['){
				err = i;
				break;
			}
			else{
				brackets.pop();
			}
		}		
		else if (s[i] == '}'){
			if (brackets.empty()){
				err = i;
				break;
			}
			brk e = brackets.top();
			if (e.type != '{'){
				err = i;
				break;
			}
			else{
				brackets.pop();
			}
		}
	}
	if (err != -1){
		cout << (err + 1) << endl;
	}
	else if (brackets.empty()) {
		cout << "Success" << endl;
	}
	else {
		brk t = brackets.top();
		cout << (t.pos+1) << endl;
	}
	return 0;
}