#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

const ld EPS = 1e-9;
const ld INF = 1e18;

struct Edge {
	int a, b; ld c;
};

const int N = 100+1;
int x[N], y[N], deg[N];
string name[N];
ld dist[N][N];
vector<int> adj[N];
bool seen[N];

ld distance(ld a, ld b, ld s, ld t) {
	return sqrt((a-s)*(a-s) + (b-t)*(b-t));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		unordered_map<string,int> idx;
		for(int i=1; i<=n; i++) {
			cin >> name[i] >> x[i] >> y[i];
			idx[name[i]] = i;
			seen[i] = false;
			adj[i].clear();
			deg[i] = 0;
		}

		fill(&dist[0][0], &dist[0][0]+N*N, INF);
		for(int i=0; i<=n; i++) {
			dist[i][i] = 0;
		}

		for(int i=0; i<m; i++) {
			string o, s, t, _;
			cin >> o >> _ >> s >> _ >> _ >> t;
			int a = idx[s];
			int b = idx[t];
			int c = idx[o];
			assert(a && b && c);
			ld da = distance(x[a], y[a], x[c], y[c]);
			ld db = distance(x[b], y[b], x[c], y[c]);
			dist[b][a] = db-da - 7*EPS;
			if(!seen[a]) {
				seen[a] = true;
				dist[0][a] = 0;
			}
			if(!seen[b]) {
				seen[b] = true;
				dist[0][b] = 0;
			}
		}

		for(int k=0; k<=n; k++) {
			for(int i=0; i<=n; i++) {
				for(int j=0; j<=n; j++) {
					dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}

		bool ok = true;
		for(int i=1; i<=n; i++) {
			if(dist[i][i] < 0) {
				ok = false;
			}
		}
		if(!ok) {
			cout << "IMPOSSIBLE" << nl;
			continue;
		}

		for(int i=1; i<=n; i++) {
			if(!seen[i]) continue;
			for(int j=1; j<i; j++) {
				if(!seen[j]) continue;
				ok &= (dist[i][j] < 0 || dist[j][i] < 0);
				if(dist[i][j] < 0) {
					adj[j].push_back(i);
					deg[i]++;
				} else {
					adj[i].push_back(j);
					deg[j]++;
				}
			}
		}

		if(!ok) {
			cout << "UNKNOWN" << nl;
		} else {
			vector<int> res;
			queue<int> bfs;
			for(int i=1; i<=n; i++) {
				if(deg[i] == 0 && seen[i]) {
					bfs.push(i);
				}
			}
			while(!bfs.empty()) {
				int u = bfs.front();
				bfs.pop();
				res.push_back(u);
				for(int v : adj[u]) {
					if(--deg[v] == 0) {
						bfs.push(v);
					}
				}
			}
			for(int u:res) {
				cout << name[u] << " ";
			}
			cout << nl;
		}
	}


}
