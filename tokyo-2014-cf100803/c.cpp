#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';
const int N = 1010;

int a[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(10);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int c, d; cin >> c >> d;
		a[c] = max(a[c], d);
	}
	int ans = 0, l = -1, r = -1;
	for (int i = 0; i <= n; i++, ans++) {
		if (i == r) {
			ans += 2*(r - l);
			l = r = -1;
		}
		if (l == -1 && a[i]) {
			l = i;
			r = a[i];
		} else if (a[i]) {
			r = max(r, a[i]);
		}
	}
	cout << ans << nl;
	return 0;
}
