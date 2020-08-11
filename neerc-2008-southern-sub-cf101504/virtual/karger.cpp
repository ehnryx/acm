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

const int N = 51;
int root[N];
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

struct Edge {
	int a, b, id;
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	vector<Edge> edges;
	for (int i=1; i<=m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		while (c--) {
			edges.push_back({a,b,i});
		}
	}

	int best = INF;
	set<int> ans;

	while (clock() < 1.789*CLOCKS_PER_SEC) {
		for (int i=1; i<=n; i++) {
			shuffle(edges.begin(), edges.end(), rng);
			memset(root, -1, sizeof root);

			int nodes = n;
			for (const Edge& e : edges) {
				if (nodes <= 3) break;
				if (e.a == i || e.b == i) continue;
				nodes -= link(e.a, e.b);
			}

			set<int> cur;
			int cut = 0;
			for (const Edge& e : edges) {
				if (e.a == i || e.b == i) continue;
				if (find(e.a) != find(e.b)) {
					cut++;
					cur.insert(e.id);
				}
			}

			if (cut < best) {
				best = cut;
				ans = cur;
			}
		}
	}

	cout << best << nl;
	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << ' ';
	}
	cout << nl;

	return 0;
}
