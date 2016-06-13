#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <set>

using namespace std;

struct Node{
	string val;
	Node *next;
};

class List
{
public:
	Node *head = NULL;
	void insert(string x){
		if (head == NULL){
			Node *n = new Node;
			n->val = x;
			n->next = NULL;
			head = n;
		}
		else if (!exist(x)){
			Node *n = new Node;
			n->val = x;
			n->next = head;
			head = n;
		}
	}
	bool exist(string x){
		Node *ptr = head;
		bool exist = false;
		while(ptr != NULL){
			if (ptr->val == x){
				exist = true;
				break;
			}
			ptr = ptr->next;
		}
		return exist;
	}
	void del(string x){
		Node *ptr = head;
		if (ptr && ptr->val == x){
			head = head->next;
		}
		else {
			while(ptr != NULL){
				if (ptr->next && ptr->next->val == x){
					ptr->next = ptr->next->next;
					break;
				}
				ptr = ptr->next;
			}
		}
	}
	void iter(){
		Node *ptr = head;
		while(ptr != NULL){
			cout << ptr->val << " ";
			ptr = ptr->next;
		}
		cout << endl;
	}
};

class HashTable
{
private:
	long long hash(string x){
		long long val = 0;
		for(int i = x.size()-1; i > -1 ; i--){
			val = ((val*factor + x[i]) % p);
		}
		val = val % buckets;
		return val;
	}
	vector<long long> powers;
	int buckets;
	int p = 1e9+7;
	int factor = 263;
	int str_limit = 1e5;
	vector<List> hash_arr;
public:
	HashTable(int m);
	~HashTable();
	void insert(string x){
		long long hash_val = hash(x);
		hash_arr[hash_val].insert(x);
	}
	void del(string x){
		long long hash_val = hash(x);
		hash_arr[hash_val].del(x);
	}
	void find(string x){
		long long hash_val = hash(x);
		if (hash_arr[hash_val].exist(x)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	void check(int i){
		hash_arr[i].iter();
	}
};

HashTable::HashTable(int m){
	powers.resize(str_limit);
	//calculate powers for future use
	for(int i = 0; i < str_limit; i++){
		if (i == 0) powers[i] = 1;
		else {
			powers[i] = (powers[i-1]*factor) % p;
		}
	}
	buckets = m;
	hash_arr.resize(m);
	for(int i = 0; i < m; i++){
		List s;
		hash_arr[i] = s;
	}
}

HashTable::~HashTable(){

}

int main(int argc, char const *argv[])
{
	int m, n;
	cin >> m >> n;
	HashTable table(m);
	for(int i = 0; i < n; i++){
		string x;
		cin >> x;
		if (x == "add"){
			string val;
			cin >> val;
			table.insert(val);
		}
		if (x == "find"){
			string val;
			cin >> val;
			table.find(val);
		}
		if (x == "check"){
			int val;
			cin >> val;
			table.check(val);
		}
		if (x == "del"){
			string val;
			cin >> val;
			table.del(val);
		}
	}
	return 0;
}