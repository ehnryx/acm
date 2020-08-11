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

const int N = 1e6+1;
vector<int> adj[2][N];
int a[N], deg[N], ans[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
	freopen("tour.in", "r", stdin);
#endif

	int T;
	cin >> T;
	while (T--) {

		int n;
		cin >> n;

		for (int i=0; i<n; i++) {
			adj[0][i].clear();
			adj[1][i].clear();
			deg[i] = 0;
			ans[i] = 0;
		}

		vector<pii> p;
		for (int i=0; i<n; i++) {
			cin >> a[i];
			p.push_back(pii(a[i], i));
		}
		sort(p.begin(), p.end(), greater<pii>());

		set<int> idx;
		for (const pii& it : p) {
			int i = it.second;
			auto jt = idx.upper_bound(i);
			if (jt != idx.end()) {
				adj[0][*jt].push_back(i);
				deg[i]++;
			}
			if (jt != idx.begin()) {
				adj[1][*prev(jt)].push_back(i);
				deg[i]++;
			}
			idx.insert(i);
		}

		queue<int> bfs;
		for (int i=0; i<n; i++) {
			for (int t=0; t<2; t++) {
				sort(adj[t][i].begin(), adj[t][i].end());
			}
			if (deg[i] == 0) {
				bfs.push(i);
			}
		}

		int maxv = 0;
		while (!bfs.empty()) {
			int u = bfs.front();
			bfs.pop();
			if (!ans[u]) {
				ans[u] = 1;
			}
			maxv = max(maxv, ans[u]);
			for (int t=0; t<2; t++) {
				set<int> cur;
				for (int i=1; i<=3; i++) cur.insert(i);
				cur.erase(ans[u]);
				int m = adj[t][u].size();
				int val = 0;
				int id = 0;
				for (int i=0; i<m; i++) {
					if (ans[adj[t][u][i]]) {
						val = ans[adj[t][u][i]];
						id = i;
						break;
					}
				}
				if (val) {
					cur.erase(val);
				}
				for (int i=0; i<m; i++) {
					if (i%2 == id%2) {
						if (val) ans[adj[t][u][i]] = val;
						else ans[adj[t][u][i]] = *cur.begin();
					} else {
						ans[adj[t][u][i]] = *cur.rbegin();
					}
					deg[adj[t][u][i]]--;
					if (deg[adj[t][u][i]] == 0) {
						bfs.push(adj[t][u][i]);
					}
				}
			}
		}

		cout << maxv << nl;
		for (int i=0; i<n; i++) {
			cout << ans[i] << " ";
		}
		cout << nl;

	}

	return 0;
}
