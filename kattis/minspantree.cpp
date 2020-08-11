#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
	int a, b, c;
	bool operator < (const Edge& o) const {
		return c < o.c;
	}
};

const int N = 2e4+1;
struct DSU {
	int root[N];
	void init(int n) { memset(root, -1, n*sizeof(int)); }
	int find(int i) {
		if (root[i] == -1) return i;
		return root[i] = find(root[i]);
	}
	int link(int i, int j) {
		i = find(i); j = find(j);
		if (i == j) return false;
		root[i] = j;
		return true;
	}
} dsu;

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	for (int n,m; cin>>n>>m && n; ) {
		vector<Edge> edges;
		for (int i=0; i<m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			edges.push_back({a,b,c});
		}
		sort(edges.begin(), edges.end());

		dsu.init(n);
		vector<pii> ans;
		int sum = 0;
		for (const Edge& e : edges) {
			if (dsu.link(e.a, e.b)) {
				ans.push_back({min(e.a,e.b),max(e.a,e.b)});
				sum += e.c;
			}
		}

		if (ans.size() < n-1) {
			cout << "Impossible" << nl;
		} else {
			sort(ans.begin(), ans.end());
			cout << sum << nl;
			for (const pii& e : ans) {
				cout << e.first << " " << e.second << nl;
			}
		}
	}

	return 0;
}
