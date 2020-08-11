#include <bits/stdc++.h>
using namespace std;
#define FILENAME "froggy"

#define nl '\n'
typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
const int N = 1010;

int S, T;
int w, n;
pt ps[N];

ld d[N][N];
pair<int, bool> par[N][2];
bool vis[N][2];
pt ans(0.5, 0.5);

bool check(ld lim) {
	//cerr << "check " << lim << nl;
	memset(vis, 0, sizeof vis);
	queue<pair<int, bool>> q;
	q.emplace(S, 1);
	vis[S][1] = 1;
	while (!q.empty()) {
		int u; bool b; tie(u, b) = q.front(); q.pop();
		for (int i = 0; i < n; i++) {
			if (d[u][i] <= lim) {
				if (!vis[i][b]) {
					vis[i][b] = 1;
					par[i][b] = {u, b};
					q.emplace(i, b);
				}
			} else if (b && d[u][i] <= 2*lim) {
				if (!vis[i][0]) {
					vis[i][0] = 1;
					par[i][0] = {u, b};
					q.emplace(i, 0);
				}
			}
		}
	}
	if (!vis[T][0] && !vis[T][1]) return 0;
	if (vis[T][1]) return 1;
	pair<int, bool> cur(T, 0);
	while (1) {
		auto p = par[cur.first][cur.second];
		if (p.second) {
			if (cur.first == T) {
				pt tt = pt(w, ps[p.first].imag());
				ans = (tt + ps[p.first]) / 2.0;
				return 1;
			}
			if (p.first == S) {
				pt ss = pt(0, ps[cur.first].imag());
				ans = (ps[cur.first] + ss) / 2.0;
				return 1;
			}
			ans = (ps[cur.first] + ps[p.first]) / 2.0;
			return 1;
		}
		cur = p;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif

	cin >> w >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		ps[i] = pt(x, y);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			d[i][j] = d[j][i] = abs(ps[i] - ps[j]);
		}
	}
	S = n;
	T = n+1;
	for (int i = 0; i < n; i++) {
		d[S][i] = d[i][S] = ps[i].real();
		d[T][i] = d[i][T] = w - ps[i].real();
	}
	ps[S] = pt(0, 0);
	ps[T] = pt(w, 0);
	d[S][T] = d[T][S] = w;
	n += 2;
	ld l = 0, r = 3e9;
	for (int i = 0; i < 60; i++) {
		ld mid = (l+r)/2;
		if (check(mid)) r = mid;
		else l = mid;
	}
	check(l);
	cout << fixed << setprecision(10) << ans.real() << " " << ans.imag() << nl;

	return 0;
}
