#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

ostream& operator << (ostream& os, const pii& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m, source, sink;
	while (cin >> n >> m >> source >> sink) {
		vector<int> adj[n+1];
		map<int,int> rev[n+1];
		map<pii,set<int>> edges;
		cerr << endl;

		int a, b;
		for (int i = 0; i < m; i++) {
			cin >> a >> b;
			adj[a].push_back(b);
			rev[b][a]++;
			edges[pii(a,b)].insert(i+1);
		}

		if (!rev[source].empty() || !adj[sink].empty()) {
			cerr << "bad graph" << endl;
			cout << "NO" << nl;
			continue;
		}
		cerr << "OK graph built" << endl << endl;

		int vis;
		stack<int> next;
		vector<int> parent(n+1, -1);
		vector<int> rev_par(n+1, -1);

		vis = 0;
		parent[source] = 0;
		next.push(source);
		while (!next.empty()) {
			int cur = next.top();
			next.pop();
			vis++;
			for (int x : adj[cur]) {
				if (parent[x] == -1) {
					parent[x] = cur;
					next.push(x);
					if (rev[x][cur] == 1) {
						rev[x].erase(cur);
					} else {
						rev[x][cur]--;
					}
				}
			}
		}
		if (vis != n) {
			cerr << "no forward tree" << endl;
			cout << "NO" << nl;
			continue;
		}
		cerr << "OK found forward tree" << endl << endl;
		cerr; for (int i = 1; i <= n; i++) cerr << parent[i] << " "; cerr << endl;

		rev_par[sink] = 0;
		next.push(sink);
		while (!next.empty()) {
			int cur = next.top();
			next.pop();
			for (const pii& it : rev[cur]) {
				cerr << "edge " << it << endl;
				if (rev_par[it.first] == -1) {
					rev_par[it.first] = cur;
					next.push(it.first);
				}
			}
		}
		cerr << "OK reverse tree tentative" << endl << endl;
		cerr; for (int i = 1; i <= n; i++) cerr << rev_par[i] << " "; cerr << endl;

		vector<int> degree(n+1, 0);
		queue<int> topo;
		for (int i = 1; i <= n; i++) {
			if (rev_par[i] != -1) {
				if (rev[rev_par[i]][i] == 1) {
					rev[rev_par[i]].erase(i);
				} else {
					rev[rev_par[i]][i]--;
				}
			}
			else {
				for (int x : adj[i]) {
					if (rev_par[x] == -1) {
						degree[i]++;
					}
				}
				if (degree[i] == 0) {
					topo.push(i);
					cerr << "push unvisited " << i << endl;
				}
			}
		}
		cerr << "OK pushed stuff to queue" << endl << endl;

		while (!topo.empty()) {
			int cur = topo.front();
			topo.pop();
			for (int x : adj[cur]) {
				if (!rev[x].empty()) {
					auto it = rev[x].begin();
					parent[x] = it->first;
					rev_par[cur] = x;
					if (it->second == 1) {
						rev[x].erase(it);
					} else {
						it->second--;
					}
					break;
				}
			}
		}
		cerr << "OK resolved conflicts" << endl;
		cerr; for (int i = 1; i <= n; i++) cerr << parent[i] << " "; cerr << endl;
		cerr; for (int i = 1; i <= n; i++) cerr << rev_par[i] << " "; cerr << endl;

		vis = true;
		for (int i = 1; i <= n; i++) {
			if (rev_par[i] == -1) {
				vis = false;
				break;
			}
		}
		if (!vis) {
			cerr << "no reverse tree" << endl;
			cout << "NO" << nl;
			continue;
		}

		cerr << "ANSWER: " << endl;
		cout << "YES" << nl;
		for (int i = 1; i <= n; i++) {
			cerr << ";parent " << i << ": " << parent[i] << endl;
			if (parent[i] != 0) {
				auto it = edges.find(pii(parent[i], i));
				assert(!it->second.empty());
				cout << *it->second.begin() << " ";
				it->second.erase(it->second.begin());
			}
		}
		cout << nl;
		for (int i = 1; i <= n; i++) {
			cerr << ";rev_par " << i << ": " << rev_par[i] << endl;
			if (rev_par[i] != 0) {
				auto it = edges.find(pii(i, rev_par[i]));
				assert(!it->second.empty());
				cout << *it->second.begin() << " ";
				it->second.erase(it->second.begin());
			}
		}
		cout << nl;
	}

	return 0;
}
