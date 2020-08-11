#include <bits/stdc++.h>
using namespace std;
#define problem_name "folding"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

int lg(int x) {
	if (x == 1) return 0;
	return 32 - __builtin_clz(x-1);
}

int solve(int a, int b, int x, int y) {
	if (x > a || y > b) return INF;
	return lg((a+x-1)/x) + lg((b+y-1)/y);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(problem_name ".in", "r", stdin);
	freopen(problem_name ".out", "w", stdout);
#endif

	int a, b, x, y;
	cin >> a >> b >> x >> y;
	int ans = min(solve(a,b,x,y), solve(a,b,y,x));
	if (ans == INF) {
		cout << -1 << nl;
	} else {
		cout << ans << nl;
	}

	return 0;
}
