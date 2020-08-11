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
const int N = 10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int dx[] = {2, -2}, dy[] = {2, 2};

struct edge {
	int x, y, i;
};

struct Edge {
	int a, b, x, y;
};

vector<string> grid(10);

vector<Edge> use;
vector<edge> adj[N][N];
char dp[N][N][1 << 16];
int build(int k) {
	use.clear();
	int m = 0;
	//cerr << "# " << k << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			switch (k) {
			case 0: if (!(i%2 == 0 && (i/2+j/2)%2 == 0)) continue;
					break;
			case 1: if (!(i%2 == 0 && (i/2+j/2)%2)) continue;
					break;
			case 2: if (!(i%2 && (i/2+j/2)%2 == 0)) continue;
					break;
			case 3: if (!(i%2 && (i/2+j/2)%2)) continue;
					break;
			}
			for (int l = 0; l < 2; l++) {
				if (i+dx[l] < 0 || i+dx[l] >= N || j+dy[l] < 0 || j+dy[l] >= N) continue;
				if ((grid[i][j] == '#' || grid[i][j] == 'W')
					&& (grid[i+dx[l]][j+dy[l]] == '#' || grid[i+dx[l]][j+dy[l]] == 'W')
					&& (grid[i+dx[l]/2][j+dy[l]/2] == 'B')) {
					//cerr << "ADD (" << i << " " << j << ") (" << i+dx[l] << " " << j+dy[l] << ")" << endl;
					adj[i][j].push_back({i+dx[l], j+dy[l], m});
					adj[i+dx[l]][j+dy[l]].push_back({i, j, m});
					use.push_back({i, j, i+dx[l], j+dy[l]});
					m++;
				}
			}
		}
	}
	////cerr << m << endl;
	assert(m<=16);
	return m;
}

struct DSU {
	int root[100];
	void clear() { memset(root, -1, sizeof root); }
	int find(int i) { 
		if (root[i] == -1) return i;
		return root[i] = find(root[i]);
	}
	bool link(int i, int j) {
		if (find(i) == find(j)) return false;
		root[find(i)] = find(j);
		return true;
	}
};
DSU dsu;
int seen[100];
bool solve(int bm) {
	dsu.clear();
	memset(seen, 0, sizeof seen);
	int links = 0, sz = 0;
	for (int i = 0; i < 16; i++) {
		if (bm & (1<<i)) {
			links += dsu.link(use[i].a * 10 + use[i].b, use[i].x * 10 + use[i].y);
			sz += !seen[use[i].a*10 + use[i].b] + !seen[use[i].x*10 + use[i].y];
			seen[use[i].a*10 + use[i].b]++;
			seen[use[i].x*10 + use[i].y]++;
		}
	}

	if (links + 1 != sz) {
		return false;
	}

	int white = 0;
	bitset<100> odd;
	for (int i = 0; i < 100; i++) {
		if (!seen[i]) continue;
		if (seen[i] % 2) {
			odd[i] = 1;
		}
		if (grid[i/10][i%10] == 'W') {
			white++;
		}
	}
	int dd = odd.count();
	if (dd > 2) return false;
	if (dd == 0 && white == 1) return true;
	if (dd == 2 && white == 1) {
		for (int i = 0; i < 100; i++) {
			if (odd[i])
				if (grid[i/10][i%10] == 'W') return true;
		}
		return false;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T; cin >> T;
	while (T--) {
		for (int i = 0; i < N; i++) cin >> grid[i];
		int ans = 0;
		for (int k = 0; k < 4; k++) {
			//memset(dp, -1, sizeof dp);
			for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) adj[i][j].clear();
			int edges = build(k);
			for (int bm = 1; bm < (1<<edges); bm++) {
				if (solve(bm)) ans = max(ans, __builtin_popcount(bm));
			}
		}
		cout << ans << nl;
	}

	return 0;
}
