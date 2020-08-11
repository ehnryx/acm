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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	map<string,int> idx;
	vector<string> mem;
	for (int i=0; i<n; i++) {
		string s;
		cin >> s;
		mem.push_back(s);
		idx[s] = i;
	}

	vector<int> adj[n];
	int dist[n][n];
	memset(dist, INF, sizeof dist);

	for (int i=0; i<n; i++) {
		string s; int k;
		cin >> s >> k;
		int id = idx[s];
		for (int j=0; j<k; j++) {
			string t;
			cin >> t;
			for(;;) {
				cin >> t;
				if (t.back() == ',') {
					t.pop_back();
					dist[id][idx[t]] = 1;
					adj[id].push_back(idx[t]);
				} else {
					dist[id][idx[t]] = 1;
					adj[id].push_back(idx[t]);
					break;
				}
			}
		}
	}

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			for (int k=0; k<n; k++) {
				dist[i][k] = min(dist[i][k], dist[i][j]+dist[j][k]);
			}
		}
	}

	int bad = 0;
	for (int i=0; i<n; i++) {
		if (dist[i][i] < dist[bad][bad]) {
			bad = i;
		}
	}

	if (dist[bad][bad] == INF) {
		cout << "SHIP IT" << nl;
	} else {
		int pre[n]; memset(pre, -1, sizeof pre);
		queue<int> bfs;
		for (int x : adj[bad]) {
			bfs.push(x);
			pre[x] = bad;
		}
		while (!bfs.empty()) {
			int u = bfs.front(); bfs.pop();
			if (u == bad) break;
			for (int x : adj[u]) {
				if (pre[x] == -1) {
					pre[x] = u;
					bfs.push(x);
				}
			}
		}
		vector<int> ans = {bad};
		for (int t=pre[bad]; t!=bad; t=pre[t]) {
			ans.push_back(t);
		}
		reverse(ans.begin(), ans.end());
		for (int it : ans) {
			cout << mem[it] << " ";
		}
		cout << nl;
	}

	return 0;
}
