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
	int i, j, s;
	bool operator < (const Node& o) const {
		return s < o.s;
	}
};

const int N = 500*501+1;
const int M = 500+1;
string grid[M];
int toss[M], score[M];
int dist[N];

void solve() {
	int n, m;
	cin >> n >> m;

	function<int(int,int)> get = [=] (int i, int j) {
		return i*m + j;
	};

	for (int i=0; i<m; i++) {
		cin >> toss[i];
	}
	for (int i=0; i<n; i++) {
		cin >> grid[i];
		for (int j=0; j<m; j++) {
			if (grid[i][j] == '\\') {
				grid[i][j] = '/';
			}
		}
	}
	for (int i=0; i<m; i++) {
		cin >> score[i];
	}

	priority_queue<Node> dijk;
	for (int i=0; i<m; i++) {
		dijk.push({n, i, score[i]});
	}

	fill(dist, dist+(n+1)*m, -1);
	while (!dijk.empty()) {
		Node cur = dijk.top();
		dijk.pop();
		int u = get(cur.i,cur.j);
		if (dist[u] == -1) {
			dist[u] = cur.s;
			if (cur.i > 0) {
				dijk.push({cur.i-1, cur.j, cur.s});
				if (cur.j > 0 && grid[cur.i-1][cur.j-1] == '/' && dist[get(cur.i-1,cur.j-1)] == -1) {
					dijk.push({cur.i-1, cur.j-1, cur.s});
				}
				if (cur.j+1 < m && grid[cur.i-1][cur.j+1] == '/' && dist[get(cur.i-1,cur.j+1)] == -1) {
					dijk.push({cur.i-1, cur.j+1, cur.s});
				}
			}
		}
	}

	ll ans = 0;
	for (int i=0; i<m; i++) {
		if (dist[get(0,i)] != -1) {
			ans += (ll)toss[i]*dist[get(0,i)];
		}
	}
	cout << ans << nl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#define FILENAME "balls"
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
