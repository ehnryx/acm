#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 1 + 10 + 26 + 26;




int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	vector<char> all;
	all.push_back(' ');
	for (char c = '0'; c <= '9'; c++) all.push_back(c);
	for (char c = 'A'; c <= 'Z'; c++) all.push_back(c);
	for (char c = 'a'; c <= 'z'; c++) all.push_back(c);

	int n = all.size();
	assert(n == N);

	map<char,int> idx;
	for (int i=0; i<n; i++) {
		idx[all[i]] = i;
	}
	
	auto remap = [&] (char c) {
		if (c == '0') return '!';
		else if (c == 'A') return ':';
		else if (c == 'a') return '[';
		else return c;
	};

	auto solve = [&] (const bitset<N>& seen) {
		string ans;
		for (int i=0; i<N; ) {
			if (!seen[i]) {
				i++;
			} else {
				int j = i+1;
				for ( ; j<N && seen[j]; j++) ;
				if (j-i < 3) {
					for (int k=i; k<j; k++) {
						ans.push_back(all[k]);
					}
				} else {
					ans.push_back(remap(all[i]));
					ans.push_back('-');
					ans.push_back(all[j-1]);
				}
				i = j;
			}
		}
		return ans;
	};

	string s;
	getline(cin, s);
	bitset<N> seen;
	for (char c : s) {
		seen.set(idx[c]);
	}
	string a = "\%[" + solve(seen) + "]";
	string b = "\%[^" + solve(~seen) + "]";
	if (b.size() == 4) cout << "\%[^!]" << nl;
	else if (a.size() < b.size()) cout << a << nl;
	else if (b.size() < a.size()) cout << b << nl;
	else cout << min(a,b) << nl;

	return 0;
}
