#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

const int N = 1e2+2;
vector<pii> adj[N][N];
vector<pii> rev[N][N];
int from[N][N];
int to[N][N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	vector<pii> move;
	vector<string> res;
	for (int i=1; i<N; i++) {
		move.push_back(pii(0,i));
		move.push_back(pii(-i,0));
		move.push_back(pii(i,0));
		move.push_back(pii(0,-i));
		res.push_back(to_string(i)+"E");
		res.push_back(to_string(i)+"N");
		res.push_back(to_string(i)+"S");
		res.push_back(to_string(i)+"W");
	}

	int n, m;
	string s;

	for (int cs = 1; ; cs++) {
		cin >> n >> m;
		if (!n && !m) break;

		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				adj[i][j].clear();
				rev[i][j].clear();
			}
		}

		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				if (i == n && j == m) break;
				cin >> s;
				char c = s.back();
				s.pop_back();
				int d = stoi(s);

				if (c == 'S' && i+d <= n) {
					adj[i][j].push_back(pii(i+d,j));
					rev[i+d][j].push_back(pii(i,j));
				} else if (c == 'E' && j+d <= m) {
					adj[i][j].push_back(pii(i,j+d));
					rev[i][j+d].push_back(pii(i,j));
				} else if (c == 'N' && i-d > 0) {
					adj[i][j].push_back(pii(i-d,j));
					rev[i-d][j].push_back(pii(i,j));
				} else if (c == 'W' && j-d > 0) {
					adj[i][j].push_back(pii(i,j-d));
					rev[i][j-d].push_back(pii(i,j));
				}
			}
		}

		memset(from, INF, sizeof from);
		memset(to, INF, sizeof to);
		queue<pii> bfs;

		bfs.push(pii(1,1));
		from[1][1] = 0;
		while (!bfs.empty()) {
			int i, j;
			tie(i,j) = bfs.front();
			bfs.pop();
			//cerr << "forward " << i << " " << j << " " << from[i][j] << nl;
			for (pii x : adj[i][j]) {
				if (from[x.first][x.second] == INF) {
					from[x.first][x.second] = from[i][j]+1;
					bfs.push(x);
				}
			}
		}

		bfs.push(pii(n,m));
		to[n][m] = 0;
		while (!bfs.empty()) {
			int i, j;
			tie(i,j) = bfs.front();
			bfs.pop();
			//cerr << "badcard " << i << " " << j << " " << to[i][j] << nl;
			for (pii x : rev[i][j]) {
				if (to[x.first][x.second] == INF) {
					to[x.first][x.second] = to[i][j]+1;
					bfs.push(x);
				}
			}
		}

		int best = from[n][m];
		pii pos(0,0);
		int ans = -1;
		for (int i=1; i<=n; i++) {
			for (int j=1; j<=m; j++) {
				for (int k = 0; k < move.size(); k++) {
					pii x = move[k];
					int ni = x.first+i;
					int nj = x.second+j;
					if (0 < ni && ni <= n && 0 < nj && nj <= m) {
						int cur = from[i][j] + to[ni][nj] + 1;
						if (cur < best) {
							best = cur;
							pos = pii(i,j);
							ans = k;
						}
					}
				}
			}
		}

		cout << "Case " << cs << ": ";
		if (best == INF) {
			cout << "impossible" << nl;
		} else if (ans == -1) {
			cout << "none " << best << nl;
		} else {
			cout << pos.first-1 << " " << pos.second-1 << " " << res[ans] << " " << best << nl;
		}
	}

	return 0;
}
