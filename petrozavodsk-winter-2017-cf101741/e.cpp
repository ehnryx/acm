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

template <class T>
ostream& operator << (ostream& os, const pair<T,T>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}

struct Hash_pii {
	unsigned int operator() (const pii& v) const {
		hash<int> h;
		return h(v.first) ^ h(v.second);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m, source, sink;
	while (cin >> n >> m >> source >> sink) {
		unordered_map<int,int> adj[n+1];
		unordered_map<int,int> rev[n+1];
		unordered_map<pii,unordered_set<int>,Hash_pii> edges;
		vector<int> in(n+1, -1), out(n+1, -1);
		in[source] = 0;
		out[sink] = 0;

		int a, b;
		for (int i = 1; i <= m; i++) {
			cin >> a >> b;
			adj[a][b]++;
			rev[b][a]++;
			edges[pii(a,b)].insert(i);
		}
		//cerr << "OK input" << endl;

		unordered_set<int> seen[2];
		queue<pii> nodes;
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() == 1) {
				//cerr << "forward: push " << i << endl;
				nodes.push(pii(i, 0));
			} else if (i != sink) {
				seen[0].insert(i);
			}
			if (rev[i].size() == 1) {
				//cerr << "reverse: push " << i << endl;
				nodes.push(pii(i, 1));
			} else if (i != source) {
				seen[1].insert(i);
			}
		}
		//cerr << "OK pushed nodes" << endl;

redo:
		while (!nodes.empty()) {
			pii cur = nodes.front();
			nodes.pop();
			int i = cur.first;
			//cerr << " visit " << cur << endl;

			int x, cnt;
			if (cur.second == 1) {
				if (rev[i].empty()) {
					goto broken;
				}
				tie(x, cnt) = *rev[i].begin();
				in[i] = x;
				if (cnt == 1) {
					rev[i].erase(x);
					adj[x].erase(i);
				} else {
					rev[i][x]--;
					adj[x][i]--;
				}
				if (seen[0].count(x) && adj[x].size() == 1) {
					nodes.push(pii(x, 0));
					seen[0].erase(x);
				}
			}

			else {
				if (adj[i].empty()) {
					goto broken;
				}
				tie(x, cnt) = *adj[i].begin();
				out[i] = x;
				if (cnt == 1) {
					adj[i].erase(x);
					rev[x].erase(i);
				} else {
					adj[i][x]--;
					rev[x][i]--;
				}
				if (seen[1].count(x) && rev[x].size() == 1) {
					nodes.push(pii(x, 1));
					seen[1].erase(x);
				}
			}
		}
		if (!seen[0].empty()) {
			nodes.push(pii(*seen[0].begin(), 0));
			seen[0].erase(seen[0].begin());
			goto redo;
		}
		if (!seen[1].empty()) {
			nodes.push(pii(*seen[1].begin(), 1));
			seen[1].erase(seen[1].begin());
			goto redo;
		}

		//cerr << "OK saturated edges" << endl;
		//cerr << "IN  tree: "; for (int i = 1; i <= n; i++) //cerr << in[i] << " "; //cerr << endl;
		//cerr << "OUT tree: "; for (int i = 1; i <= n; i++) //cerr << out[i] << " "; //cerr << endl;

broken:
		bool bad = false;
		vector<int> ans_in, ans_out;
		for (int i = 1; i <= n; i++) {
			if (in[i] == -1 || out[i] == -1) {
				bad = true;
				break;
			}
			else {
				if (in[i] != 0) {
					auto it = edges[pii(in[i], i)].begin();
					ans_in.push_back(*it);
					edges[pii(in[i], i)].erase(it);
				}
				if (out[i] != 0) {
					auto it = edges[pii(i, out[i])].begin();
					ans_out.push_back(*it);
					edges[pii(i, out[i])].erase(it);
				}
			}
		}

		if (bad) {
			cout << "NO" << nl;
		}
		else {
			cout << "YES" << nl;
			for (int i : ans_in) {
				cout << i << " ";
			}
			cout << nl;
			for (int i : ans_out) {
				cout << i << " ";
			}
			cout << nl;
		}
	}

	return 0;
}
