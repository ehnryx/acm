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

struct Node {
	int id, root, dist;
	bool operator < (const Node& o) const {
		if (dist != o.dist) return dist > o.dist;
		else return id > o.id;
	}
};

const int N = 1e5+1;
vector<int> adj[N];
int c[N], res[N];
set<int> s[N], con[N];

bool cmp(int a, int b) {
	return res[a] > res[b];
}

void solve() {
	int n, m;
	cin >> n >> m;

	for (int i=1; i<=n; i++) {
		adj[i].clear();
		con[i].clear();
		s[i].clear();
		res[i] = 0;
	}

	priority_queue<Node> bfs;
	vector<int> blue;
	for (int i=1; i<=n; i++) {
		cin >> c[i];
		blue.push_back(i);
		if (c[i] == 1) {
			bfs.push({i,0,0});
		} else if (c[i] == 2) {
			bfs.push({i,i,0});
			s[i].insert(i);
		}
	}

	for (int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	while (!bfs.empty()) {
		Node cur = bfs.top();
		bfs.pop();
		int u = cur.id;
		int r = cur.root;
		if (r) {
			for (int v : adj[u]) {
				if (c[v] == 0) {
					c[v] = 2;
					s[v].insert(r);
					bfs.push({v,r,cur.dist+1});
				} else if (c[v] == 2 && !s[v].count(r) && s[v].size() <= 2) {
					s[v].insert(r);
					bfs.push({v,r,cur.dist+1});
				}
			}
		} else {
			for (int v : adj[u]) {
				if (c[v] == 0) {
					c[v] = 1;
					s[v].insert(s[u].begin(), s[u].end());
					bfs.push({v,0,cur.dist+1});
				} else if (c[v] == 2 && s[v].size() <= 2) {
					s[v].insert(s[u].begin(), s[u].end());
					if (s[v].size() <= 2) {
						c[v] = 1;
						bfs.push({v,0,cur.dist+1});
					}
				}
			}
		}
	}

	map<pii,int> pcnt;
	int base = 0;
	for (int i=1; i<=n; i++) {
		//cerr << i << ": " << c[i] << " -> "; for (int it : s[i]) {
			//cerr << it << " "; }
		//cerr << nl;
		if (c[i] == 1) {
			assert(s[i].size() <= 2);
			if (s[i].size() == 2) {
				int a = *s[i].begin();
				int b = *s[i].rbegin();
				con[a].insert(b);
				con[b].insert(a);
				pcnt[pii(min(a,b),max(a,b))]++;
			} else if (s[i].size() == 1) {
				res[*s[i].begin()]++;
			} else {
				assert(s[i].empty());
				base++;
			}
		}
	}

	int ans = 0;
	for (const auto& it : pcnt) {
		int a, b;
		tie(a,b) = it.first;
		ans = max(ans, it.second + res[a] + res[b]);
	}
	sort(blue.begin(), blue.end(), cmp);
	for (int it : blue) {
		ans = max(ans, res[it]);
		for (int jt : blue) {
			if (it != jt && !con[it].count(jt)) {
				ans = max(ans, res[it] + res[jt]);
				break;
			}
		}
	}
	//cerr << ans << " + " << base << " = ";
	cout << ans + base << nl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#define FILENAME "nodes"
	cerr << "File IO: " << FILENAME << nl;
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
#endif

	int T;
	cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}
