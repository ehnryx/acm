#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

mt19937 rng;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T = 50;
	int m = 4000;
	cout << T << nl;
	while (T--) {
		cout << m << nl;
		for (int i=0; i<m; i++) {
			cout << 0 << " " << i << " " << 0 << " " << (i+1) << " " << rng()%100000 << nl;
		}
	}

	return 0;
}
