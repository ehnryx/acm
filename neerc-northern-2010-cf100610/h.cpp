#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

#define FILE "horrible"

int main() {
	if (fopen(FILE ".in", "r")) {
		freopen(FILE ".in", "r", stdin);
		freopen(FILE ".out", "w", stdout);
	}

	int n;
	cin >> n;
	if(n == 1) {
		cout << 1 << nl;
		cout << 1 << " " << 0 << nl;
		return 0;
	}

	cout << 1 + 1 + n + (n-1)*2*(n-1) << nl;
	cout << 2 << " " << -1 << nl;
	for(int i=1; i<n; i++) {
		cout << i << " " << 0 << nl;
		for(int j=1; j<n; j++) {
			cout << (i+j-1)%n+1 << " " << i << nl;
			cout << (i+1+j-1)%n+1 << " " << -(i+1) << nl;
		}
	}
	cout << n << " " << 0 << nl;
	cout << n-1 << " " << n << nl;

	return 0;
}
