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

const int N = 1e5+1;
unordered_set<int> adj[N];
bool vis[N];

vector<int> ans;

unordered_map<int,vector<int>> cycles;
vector<vector<int>> paths;
unordered_set<int> done;

void add_cycle(int s) {
	if (done.count(s) || !cycles.count(s)) return;
	done.insert(s);

	for (int v : cycles[s]) {
		add_cycle(v);
		ans.push_back(v);
	}
}

void solve(int s) {
	if (vis[s]) return;

	cycles.clear();
	paths.clear();
	done.clear();

	unordered_set<int> even, odd;
	queue<int> connected;

	queue<int> bfs;
	bfs.push(s);
	vis[s] = true;

	while (!bfs.empty()) {
		int v = bfs.front();
		bfs.pop();
		if (adj[v].size() % 2 == 1) odd.insert(v);
		else even.insert(v);

		for (int u : adj[v]) {
			if (!vis[u]) {
				vis[u] = true;
				bfs.push(u);
			}
		}
	}

	while (!even.empty() || !connected.empty() || !odd.empty()) {
		int v;
		if (!odd.empty()) {
			v = *odd.begin();
			odd.erase(odd.begin());
		}
		else if (!connected.empty()) {
			v = connected.front();
			connected.pop();
		}
		else {
			v = *even.begin();
			even.erase(even.begin());
		}

		while (adj[v].size() > 0) {
			vector<int> cur;

			cur.push_back(v);
			for (int i = v; adj[i].size() > 0; ) {
				int j = *adj[i].begin();
				adj[i].erase(j);
				adj[j].erase(i);
				cur.push_back(j);
				connected.push(i);
				i = j;
			}

			if (cur.back() == v) {
				//cerr << "CYCLE from " << v << nl;
				cur.pop_back();
				cycles[v] = cur;
			} else {
				//cerr << "PATH from " << v << " to " << cur.back() << nl;
				paths.push_back(cur);
				even.insert(v);
				odd.erase(cur.back());
				assert(adj[cur.back()].empty());
				break;
			}
		}
	}

	for (const vector<int>& p : paths) {
		assert(p.size() > 1);
		for (int v : p) {
			add_cycle(v);
			ans.push_back(v);
		}
	}

	for (const pair<int,vector<int>>& p : cycles) {
		assert(p.second.size() > 2);
		if (!done.count(p.second.front())) {
			add_cycle(p.second.front());
			ans.push_back(p.second.front());
		}
	}
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

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		adj[a].insert(b);
		adj[b].insert(a);
	}

	for (int i = 1; i <= n; i++) {
		solve(i);
	}

	//cerr << nl << "ANSWER: " << nl;
	cout << ans.size() << nl;
	for (int it : ans) {
		cout << it << " ";
	}
	cout << nl;

	return 0;
}
