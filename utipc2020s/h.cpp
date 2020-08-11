#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;



int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	const int n = 8;
	string g[n];
	set<int> r, c;
	for(int i=0; i<n; i++) {
		cin >> g[i];
		for(int j=0; j<n; j++) {
			if(g[i][j] == 'R') {
				r.insert(i);
				c.insert(j);
			}
		}
	}
	cout << (8-r.size()) * (8-c.size()) << nl;

	return 0;
}
