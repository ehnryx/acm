#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;



int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;
	vector<int> deg(n+1);
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		deg[a]++;
		deg[b]++;
	}

	ll bad = 0;
	for(int i=1; i<=n; i++) {
		bad += (ll) deg[i] * (n-1 - deg[i]);
	}
	assert(bad % 2 == 0);
	cout << (ll)n*(n-1)*(n-2)/6 - bad/2 << nl;

	return 0;
}
