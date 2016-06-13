#include <string>
#include <iostream>
#include <vector>

using namespace std;


vector<long long> precompute_poly_hash(string &T, string &P){
	int factor = 263;
	long long PRIME = 1e9+7;
	vector<long long> powers(T.size());
	powers[0] = 1;
	for(int i = 1; i < T.size(); i++){
		powers[i] = ((powers[i-1] % PRIME)*(factor % PRIME)) % PRIME;
	}
 	int last_index = T.size()-P.size();
	vector<long long> res(T.size()-P.size()+1);
	long long first_hash = 0;
	for(int i = last_index; i < T.size(); i++){
		first_hash += ((T[i]%PRIME)*(powers[i-last_index] % PRIME)) % PRIME;
	}
	first_hash = first_hash % PRIME;
	res[last_index] = first_hash;
	for(int i = last_index-1; i > -1; i--){
		res[i] = 0;
		res[i] += T[i];
		res[i] += ((factor%PRIME)*((res[i+1] - (powers[P.size()-1]%PRIME)*(T[i+P.size()]%PRIME)) % PRIME)) % PRIME;
		res[i] = res[i] % PRIME;
		if (res[i] < 0) res[i] += PRIME;
	}
	return res;
}

long long p_hash(string &P){
	int factor = 263;
	long long PRIME = 1e9+7;
	vector<long long> powers(P.size());
	long long p_hash = 0;
	powers[0] = 1;
	for(int i = 1; i < P.size(); i++){
		powers[i] = ((powers[i-1] % PRIME)*(factor % PRIME)) % PRIME;
	}
	for(int i = 0; i < P.size(); i++){
		p_hash += ((P[i]%PRIME)*(powers[i]%PRIME)) % PRIME;
	}	
	p_hash = (p_hash+PRIME) % PRIME;
	return p_hash;
}

bool are_equal(string &T, int start, string &P){
	bool res = true;
	for(int i = start; i < start + P.size(); i++){
		if (T[i] != P[i-start]){
			res = false; break;
		}
	}
	return res;
}

void solution(string &P, string &T){
	if (P.size() > T.size()) return;
	vector<long long> hashes = precompute_poly_hash(T, P);
	long long hash = p_hash(P);
	vector<int> res;
	for(int i = 0; i < T.size()-P.size()+1; i++){
		if (hashes[i] == hash){
			if (are_equal(T, i, P)){
				res.push_back(i);
			}
		}
	}
	for(int i = 0; i < res.size(); i++){
		cout << res[i] << " ";
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
	string P, T;
	cin >> P >> T;
	solution(P, T);
	return 0;
}