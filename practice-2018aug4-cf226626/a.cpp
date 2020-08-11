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

struct Node {
	int id, pre, turns;
	Node(){}
	Node(int i, int p, int t = 0): id(i), pre(p), turns(t) {}
};

const int N = 1e3+1;
string grid[N];
vector<int> adj[N*N];
bool vis[N*N][3][2];

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

	auto get = [&] (int i, int j) {
		return i*m + j;
	};

	auto dir = [&] (int s, int t) {
		if (s/m == t/m) return 0;
		else return 1;
	};

	auto turned = [&] (int pre, int cur, int nxt) {
		if (pre == -1) return false;
		if (pre/m == cur/m && cur/m == nxt/m) return false;
		if (pre%m == cur%m && cur%m == nxt%m) return false;
		return true;
	};

	auto bfs = [&] (int s, int t) {
		queue<Node> nxt;

		nxt.push(Node(s,-1));
		while (!nxt.empty()) {
			Node cur = nxt.front();
			nxt.pop();
			if (cur.turns > 2 || vis[cur.id][cur.turns][dir(cur.pre, cur.id)]) continue;
			if (cur.id == t) return true;

			vis[cur.id][cur.turns][dir(cur.pre, cur.id)] = true;
			for (int x : adj[cur.id]) {
				nxt.push(Node(x, cur.id, cur.turns + turned(cur.pre, cur.id, x)));
			}
		}

		return false;
	};

	int s, t;
	s = t = -1;
	for (int i = 0; i < n; i++) {
		cin >> grid[i];
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 'S') {
				s = get(i,j);
			} else if (grid[i][j] == 'T') {
				t = get(i,j);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] != '*') {
				if (i > 0) adj[get(i,j)].push_back(get(i-1, j));
				if (j > 0) adj[get(i,j)].push_back(get(i, j-1));
				if (i < n-1) adj[get(i,j)].push_back(get(i+1, j));
				if (j < m-1) adj[get(i,j)].push_back(get(i, j+1));
			}
		}
	}

	cout << (bfs(s,t) ? "YES" : "NO") << nl;

	return 0;
}
