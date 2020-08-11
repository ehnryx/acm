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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os << "["; for (const T& it : v) os << it << ",";
	return os << "]";
}

template <class T>
ostream& operator << (ostream& os, const multiset<T>& v) {
	os << "{"; for (const T& it : v) os << it << ",";
	return os << "}";
}

vector<pii> edges;

vector<vector<int>> build_graph(int n, int bm) {
	vector<vector<int>> g(n);
	for (int i = 0; i < 32; i++) {
		if (bm & 1<<i) {
			int a = edges[i].first;
			int b = edges[i].second;
			g[a].push_back(b);
			g[b].push_back(a);
		}
	}
	return g;
}

bool is_connected(const vector<vector<int>>& g) {
	vector<bool> vis(g.size());
	queue<int> bfs;
	bfs.push(0);
	vis[0] = true;
	int cnt = 0;
	while (!bfs.empty()) {
		int cur = bfs.front();
		bfs.pop();
		cnt++;
		for (int x : g[cur]) {
			if (!vis[x]) {
				vis[x] = true;
				bfs.push(x);
			}
		}
	}
	return cnt == g.size();
}

multiset<vector<multiset<int>>> get_degree_set(int n, int bm) {
	vector<vector<int>> g = build_graph(n, bm);
	if (!is_connected(g)) {
		return multiset<vector<multiset<int>>>();
	}

	multiset<vector<multiset<int>>> res;
	for (int i = 0; i < n; i++) {
		vector<multiset<int>> deg(n);
		vector<int> dist(n, -1);
		queue<int> bfs;

		dist[i] = 0;
		bfs.push(i);
		while (!bfs.empty()) {
			int cur = bfs.front();
			bfs.pop();
			deg[dist[cur]].insert(g[cur].size());
			for (int x : g[cur]) {
				if (dist[x] == -1) {
					dist[x] = dist[cur]+1;
					bfs.push(x);
				}
			}
		}
		res.insert(deg);
	}
	return res;
}

bool isomorphic(int n, int bm1, int bm2) {
	vector<vector<int>> g1 = build_graph(n, bm1);
	vector<vector<int>> g2 = build_graph(n, bm2);

	vector<int> v;
	for (int i = 0; i < n; i++) {
		v.push_back(i);
	}

	do {
		bool good = true;
		for (int i = 0; i < n; i++) {
			set<int> first, second;
			for (int it : g1[i]) first.insert(v[it]);
			for (int it : g2[v[i]]) second.insert(it);
			if (first != second) {
				good = false;
				break;
			}
		}
		if (good) return true;
	} while (next_permutation(v.begin(), v.end()));

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	int m = n*(n-1)/2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			edges.push_back(pii(i,j));
		}
	}

	map<multiset<vector<multiset<int>>>,vector<int>> graphs;
	for (int bm = 0; bm < 1<<m; bm++) {
		multiset<vector<multiset<int>>> key = get_degree_set(n, bm);
		bool bad = false;
		for (const auto& it : key) {
			if (key.count(it) > 1) bad = true;
		}
		if (!bad && key.size() == n) graphs[key].push_back(bm);
	}

	cerr << graphs.size() << endl;
	for (const auto& it : graphs) {
		for (int i = 0; i < it.second.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (!isomorphic(n, it.second[i], it.second[j])) {
					cout << "GRAPHS " << nl;
					cout << it.second[i] << nl;
					cout << it.second[j] << nl;
					cout << endl;
				}
			}
		}
	}

	return 0;
}
