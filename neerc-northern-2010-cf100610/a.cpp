#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

#define FILE "acm"

int main() {
	if (fopen(FILE ".in", "r")) {
		freopen(FILE ".in", "r", stdin);
		freopen(FILE ".out", "w", stdout);
	}

	int n, m;
	cin >> n >> m;
	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
		cout << "(10";
		for(int j=0; j<a[i]; j++) {
			cout << "-1";
		}
		cout << ") * ";
	}
	cout << "1 = 0" << nl;

	return 0;
}
