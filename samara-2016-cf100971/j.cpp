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

vector<int> di = { 0, 0, 1, -1 };
vector<int> dj = { -1, 1, 0, 0 };

const int N = 2e5+1;
string grid[N];
vector<int> adj[N];
bool vis[N];

bool solve(int s, int t) {
	int maxd = 0;
	int edges = 0;
	int nodes = 0;
	queue<int> bfs;
	bfs.push(s);
	vis[s] = true;
	while (!bfs.empty()) {
		int u = bfs.front();
		bfs.pop();
		nodes++;
		maxd = max(maxd, (int)adj[u].size());
		for (int v : adj[u]) {
			edges++;
			if (!vis[v]) {
				vis[v] = true;
				bfs.push(v);
			}
		}
	}
	return vis[t] && (maxd > 2 || edges >= 2*nodes);
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

	int n, m;
	cin >> n >> m;

	for (int i=0; i<n; i++) {
		cin >> grid[i];
	}

	function<int(int,int)> get = [&] (int i, int j) {
		return i*m + j;
	};

	int s, t;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			if (grid[i][j] != '#') {
				for (int d=0; d<4; d++) {
					int ni = i+di[d];
					int nj = j+dj[d];
					if (0<=ni && ni<n && 0<=nj && nj<m && grid[ni][nj] != '#') {
						adj[get(i,j)].push_back(get(ni,nj));
					}
				}
			}
			if (grid[i][j] == '1') s = get(i,j);
			if (grid[i][j] == '2') t = get(i,j);
		}
	}

	if (solve(s,t)) cout << "YES" << nl;
	else cout << "NO" << nl;

	return 0;
}
