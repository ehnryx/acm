#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';

struct Edge {
	int x, y; ll c;
	ll ans;
	Edge(){}
	Edge(int x, int y, ll c=1, ll a=0): x(x), y(y), c(c), ans(a) {}
	bool operator < (const Edge& v) const {
		return c > v.c;
	}
};

const int N = 1e2+2;
vector<Edge> adj[N][N];
int dist[N][N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	unordered_map<int,ll> val[2];
	unordered_map<ll,string> res;
	unordered_map<ll,pii> pos;

	for (int i=1; i<=N; i++) {
		for (int j=1; j<=N; j++) {
			ll v = 1e3*(1e5+4*(i*N+j));
			for (int x=1; x<=N; x++) {
				val[1][-x] = v + 4*i;
				val[0][x] = v + 4*i+1;
				val[0][-x] = v + 4*i+2;
				val[1][x] = v + 4*i+3;
				res[val[1][-x]] = to_string(x)+"E";
				res[val[0][x]] = to_string(x)+"N";
				res[val[0][-x]] = to_string(x)+"S";
				res[val[1][x]] = to_string(x)+"W";
				pos[val[1][-x]] = pii(i,j);
				pos[val[0][x]] = pii(i,j);
				pos[val[0][-x]] = pii(i,j);
				pos[val[1][x]] = pii(i,j);
			}
		}
	}

	for(int cs = 1; ; cs++) {
		int n, m;
		cin >> n >> m;
		if (!n && !m) break;

		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				if (i == n && j == m) break;
				string s;
				cin >> s;
				char c = s.back();
				s.pop_back();
				int d = stoi(s);

				adj[i][j].clear();
				if (c == 'S' && i+d <= n) {
					adj[i][j].push_back(Edge(i+d,j));
				} else if (c == 'E' && j+d <= m) {
					adj[i][j].push_back(Edge(i,j+d));
				} else if (c == 'N' && i-d > 0) {
					adj[i][j].push_back(Edge(i-d,j));
				} else if (c == 'W' && j-d > 0) {
					adj[i][j].push_back(Edge(i,j-d));
				}

				for (int k=1; k<=n; k++) {
					if (i != k) {
						adj[i][j].push_back(Edge(k,j,val[0][i-k],val[0][i-k]));
					}
				}
				for (int k=1; k<=m; k++) {
					if (j != k) {
						adj[i][j].push_back(Edge(i,k,val[1][j-k],val[1][j-k]));
					}
				}
			}
		}

		memset(dist, -1, sizeof dist);
		priority_queue<Edge> nxt;
		nxt.push(Edge(1,1,0));
		while (!nxt.empty()) {
			Edge cur = nxt.top();
			nxt.pop();

			if (dist[cur.x][cur.y] == -1) {
				cerr << "visit " << cur.x << " " << cur.y << nl;
				dist[cur.x][cur.y] = cur.c;
				if (cur.x == n && cur.y == m) {
					cerr << "distance: " << dist[n][m] << nl;
					cout << "Case " << cs << ": ";
					if (dist[n][m] < 1e8) {
						cout << "none " << dist[n][m] << nl;
					} else if (dist[n][m] < 2e8) {
						cout << pos[cur.ans].first << " " << pos[cur.ans].second << " " << res[cur.ans] << nl;
					} else {
						cout << "impossible" << nl;
					}
					break;
				}

				for (const Edge& e : adj[cur.x][cur.y]) {
					if (e.c == 1) {
						nxt.push(Edge(e.x, e.y, e.c+cur.c, cur.ans));
					} else {
						nxt.push(Edge(e.x, e.y, e.c+cur.c, e.ans));
					}
				}
			}
		}
	}

	return 0;
}
