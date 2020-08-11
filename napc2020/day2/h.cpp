#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int INF = 0x3f3f3f3f;



int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n;
	cin >> n;
	int ans = 0;
	for(int i=0; i<n; i++) {
		int sad = INF;
		for(int j=0; j<n; j++) {
			int v;
			cin >> v;
			sad = min(sad, v);
		}
		ans = max(ans, sad);
	}
	cout << ans << nl;

	return 0;
}
