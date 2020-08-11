#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define ll long long
#define ld long double
#define pt complex<ld>
#define pol vector<pt>
#define pii pair<int,int>
#define pdd pair<ld,ld>
#define nl '\n'

const int INF = 0x3f3f3f3f;

namespace FLOW {
	const int N = 40*40 + 2;
	const int M = 40*40*6;
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M];
	void init() { m = 0; memset(first, -1, sizeof first); memset(flo, 0, sizeof flo); }
	void add_edge(int a, int b, ll c=1) {
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, ++m;
	}
	int L[N], cur[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L);
		queue<int> q; q.push(s); L[s] = 0;
		while (!q.empty()) { int u = q.front(); q.pop();
			for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
				if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
					q.push(v), L[v] = L[u]+1;
		} return L[t] < INF;
	}
	ll dfs(int u, int t, ll f) {
		if (u == t) return f;
		ll cf, df = 0;
		for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
			if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
				cf = dfs(v, t, min(cap[e]-flo[e], f-df));
				flo[e] += cf; flo[e^1] -= cf; df += cf;
			} return df;
	}
}

#define get(A,B) (A)*m+(B)

int main() {
	//ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;
	char grid[n][m+1];
	for (int i = 0; i < n; i++) {
		scanf("%s", grid[i]);
	}

	int islands = 0;
	bool visited[n][m];
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 'L' && !visited[i][j]) {
				islands++;
				queue<pii> next;
				next.push(pii(i,j));
				visited[i][j] = true;
				while (!next.empty()) {
					pii cur = next.front();
					next.pop();
					if (grid[cur.first][cur.second] == 'C') {
						grid[cur.first][cur.second] = 'W';
					} else if (grid[cur.first][cur.second] == 'L') {
						if (cur.first > 0 && !visited[cur.first-1][cur.second]) {
							visited[cur.first-1][cur.second] = true;
							next.push(pii(cur.first-1, cur.second));
						} 
						if (cur.first+1 < n && !visited[cur.first+1][cur.second]) {
							visited[cur.first+1][cur.second] = true;
							next.push(pii(cur.first+1, cur.second));
						}
						if (cur.second > 0 && !visited[cur.first][cur.second-1]) {
							visited[cur.first][cur.second-1] = true;
							next.push(pii(cur.first, cur.second-1));
						} 
						if (cur.second+1 < m && !visited[cur.first][cur.second+1]) {
							visited[cur.first][cur.second+1] = true;
							next.push(pii(cur.first, cur.second+1));
						}
					}
				}
			}
		}
	}

	int clouds = 0;
	int source = n*m;
	int sink = source+1;
	FLOW::init();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 'C') {
				clouds++;
				if ((i+j)%2) {
					FLOW::add_edge(get(i,j), sink);
				} else {
					FLOW::add_edge(source, get(i,j));
					if (i > 0 && grid[i-1][j] == 'C')
						FLOW::add_edge(get(i,j), get(i-1,j)); 
					if (j > 0 && grid[i][j-1] == 'C')
						FLOW::add_edge(get(i,j), get(i,j-1)); 
					if (i < n-1 && grid[i+1][j] == 'C')
						FLOW::add_edge(get(i,j), get(i+1,j));
					if (j < m-1 && grid[i][j+1] == 'C')
						FLOW::add_edge(get(i,j), get(i,j+1));
				}
			}
		}
	}
	
	int flow = 0;
	while (FLOW::bfs(source, sink)) {
		flow += FLOW::dfs(source, sink, INF);
	}

	cout << islands + clouds - flow << nl;

	return 0;
}
