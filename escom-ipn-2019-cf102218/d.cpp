#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int L = 18;
const int N = 1<<18;
int depth[N];
int anc[N][L];

int lca(int u, int v) {
	if (depth[u] < depth[v]) swap(u,v);
	Down(j,L) {
		if (depth[u] - (1<<j) >= depth[v]) {
			u = anc[u][j];
		}
	}
	if (u == v) return u;
	Down(j,L) {
		if (anc[u][j] != anc[v][j]) {
			u = anc[u][j];
			v = anc[v][j];
		}
	}
	return anc[u][0];
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int q;
	cin >> q;

	int last = 0;
	int curr = 1;
	depth[1] = 0;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int p;
			cin >> p;
			p = (p + last) % curr + 1;
			int u = ++curr;
			anc[u][0] = p;
			for (int j=1; j<L; j++) {
				anc[u][j] = anc[anc[u][j-1]][j-1];
			}
			depth[u] = depth[p]+1;
			last = depth[u]+1;
		} else {
			int u, v;
			cin >> u >> v;
			u = (u + last) % curr + 1;
			v = (v + last) % curr + 1;
			last = depth[u] + depth[v] - 2*depth[lca(u,v)] + 1;
		}
		cout << last << nl;
	}

	return 0;
}
