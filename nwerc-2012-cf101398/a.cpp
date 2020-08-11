#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
const int N = 1010, M = 4e4+10;

struct edge {
	int a, b, c;
};

bool used[M];
vector<edge> edges;
int d[2*N], par[2*N], pari[2*N];

int bf(int s, int t) {
	memset(d, INF, sizeof d);
	d[s] = 0;
	for (int i = 0; i < 2*N; i++) {
		for (int j = 0; j < edges.size(); j++) {
			if (used[j]) continue;
			if (d[edges[j].a] + edges[j].c < d[edges[j].b]) {
				d[edges[j].b] = d[edges[j].a] + edges[j].c;
				par[edges[j].b] = edges[j].a;
				pari[edges[j].b] = j;
			}
		}
	}
	return d[t];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int v, e;
	while (cin >> v >> e) {
		edges.clear();
		for (int i = 0; i < e; i++) {
			int a, b, c; cin >> a >> b >> c;
			edges.push_back({a+N, b, c});
		}
		for (int i = 1; i <= v; i++) {
			edges.push_back({i, i+N, 0});
		}
		memset(par, 0, sizeof par);
		memset(used, 0, sizeof used);
		int ans = bf(1+N, v);
		for (int cur = v; cur != 1+N; cur = par[cur]) {
			//cerr << cur << endl;
			used[pari[cur]] = 1;
			const edge& e = edges[pari[cur]];
			edges.push_back({e.b, e.a, -e.c});
		}
		ans += bf(1+N, v);
		cout << ans << nl;
	}

	return 0;
}
