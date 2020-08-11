#include <bits/stdc++.h>
using namespace std;
#define FILENAME "alex"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);

	int a, b;
	cin >> a >> b;

	ld ans = 0;
	ans = max(ans, min((ld)a, (ld)b/3));
	ans = max(ans, min((ld)b, (ld)a/3));
	ans = max(ans, min((ld)a/2, (ld)b/2));
	cout << fixed << setprecision(10) << ans << nl;

	return 0;
}
