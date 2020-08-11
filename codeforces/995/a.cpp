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

struct Move {
	int id, v;
};

const int N = 2 * 50*4;
vector<int> adj[N];
bitset<N> done;
bitset<N> vis;
int val[N];
int pos[N], goal[N];
int par[N];
vector<Move> ans;

bool finish(int v) {
	int s = goal[v];
	int t = pos[v];
	int cur = -1;
	vis.reset();

	queue<int> bfs;
	bfs.push(s);
	vis[s] = true;
	while (!bfs.empty()) {
		cur = bfs.front(); bfs.pop();
		if (cur == t) break;

		for (int x : adj[cur]) {
			if (!vis[x]) {
				if (val[x] == 0 || val[x] == v) {
					bfs.push(x);
					vis[x] = true;
					par[x] = cur;
				}
			}
		}
	}

	if (cur != t) {
		return false;
	}

	done[v] = true;
	for (int i = t; i != s; ) {
		i = par[i];
		ans.push_back({v,i});
	}
	return true;
}

bool movable(int v, int n) {
	int x = pos[v] / n;
	int y = pos[v] % n;
	if (y > 0 && val[pos[v]-1] == 0) {
		val[pos[v]] = 0;
		pos[v] -= 1;
		val[pos[v]] = v;
		ans.push_back({v,pos[v]});
		return true;
	}
	if (y+1 < n && val[pos[v]+1] == 0) {
		val[pos[v]] = 0;
		pos[v] += 1;
		val[pos[v]] = v;
		ans.push_back({v, pos[v]});
		return true;
	}
	if (x == 1 && val[pos[v]+n] == 0) {
		val[pos[v]] = 0;
		pos[v] += n;
		val[pos[v]] = v;
		ans.push_back({v, pos[v]});
		return true;
	}
	if (x == 2 && val[pos[v]-n] == 0) {
		val[pos[v]] = 0;
		pos[v] -= n;
		val[pos[v]] = v;
		ans.push_back({v, pos[v]});
		return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, k;
	cin >> n >> k;

	auto get = [&] (int i, int j) {
		return i*n + j;
	};
	auto add_edge = [&] (int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	};

	for (int r=0; r<4; r++) {
		for (int i=0; i<n; i++) {
			int v;
			cin >> v;
			val[get(r,i)] = v;
			if (v != 0) {
				if (r == 0 || r == 3) goal[v] = get(r,i);
				else pos[v] = get(r,i);
			}
		}
	}

	// row 1
	for (int i=0; i<n; i++) {
		add_edge(get(1,i), get(0,i));
		add_edge(get(1,i), get(2,i));
		if (i>0) add_edge(get(1,i), get(1,i-1));
		if (i+1<n) add_edge(get(1,i), get(1,i+1));
	}
	// row 2
	for (int i=0; i<n; i++) {
		add_edge(get(2,i), get(3,i));
		if (i>0) add_edge(get(2,i), get(2,i-1));
		if (i+1<n) add_edge(get(2,i), get(2,i+1));
	}

	int cnt = 0;
	while (cnt < k) {
		int before = cnt;
		for (int i=1; i<=k; i++) {
			if (!done[i] && finish(i)) {
				cnt++;
			}
		}

		if (cnt == before) {
			int memo = 0;
			int r;
			redo:
			if (++memo > 30000) {
				cout << -1 << nl;
				return 0;
			}
			while (done[r = 1+rng()%k]);
			if (!movable(r, n)) goto redo;
		}
	}

	cout << ans.size() << nl;
	for (const Move& it : ans) {
		cout << it.id << " " << 1+it.v/n << " " << 1+it.v%n << nl;
	}

	return 0;
}
