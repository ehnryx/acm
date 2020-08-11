#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;
namespace Flow {
	const int N = 501*501 + 2;
	struct Edge { int v, r; ll f, c; };
	vector<Edge> adj[N]; int sz[N]; ll mc;
	void init(int n=N) {
		mc = 0;
		fill(sz, sz+n, 0);
		fill(adj, adj+n, vector<Edge>());
	}
	void add_edge(int a, int b, ll c=1) {
		mc = max(mc, c);
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, 0});
	}
	int L[N], cur[N], Q[N];
	bool bfs(int s, int t, ll lim=1) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0;
		while(f<=b && L[t]==INF) { int u=Q[f++];
			for(const Edge& e : adj[u]) if (L[e.v]==INF && e.c-e.f >= lim) {
				Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF;
	}
	ll dfs(int u, int t, ll f) { if(u==t || !f) return f;
		for(int i=cur[u]; i<sz[u]; cur[u]=++i) { Edge& e = adj[u][i];
			if (e.f<e.c && L[e.v]==L[u]+1) {
				if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
					e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0;
	}
	ll flow(int s, int t, bool sc=0) {
		ll inf=numeric_limits<ll>::max();
		ll res = 0;
		for(ll lim=(sc?mc:1); lim; lim/=2) {
			while(bfs(s,t,lim)) while(ll cf=dfs(s,t,inf)) res += cf;
		}
		return res;
	}
}

int get(int i, int j) {
	return i*501 + j;
}

const int N = 505;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
bitset<4> edge[N][N];
bitset<4> from[N][N];
char grid[N][N];
bool seen[N][N];
bool bad;
int numBlack;

typedef pair<int,int> pii;

vector<pii> ez;

void add(int i, int j) {
	if (seen[i][j]) return;
	ez.emplace_back(i,j);
	seen[i][j] = true;
}

void takeUp(int i, int j) {
	if (from[i][j][DOWN]) {
		bad = true;
		return;
	}
	from[i][j][UP] = true;
	assert(from[i][j].count() <= 2);
	if (from[i][j].count() == 2) {
		numBlack--;
	}
	///cerr << "takeup " << i << " " << j << nl;
	assert(grid[i][j] == 'B');
	//up opposing
	if (grid[i-1][j] == 'W' && !seen[i-1][j]) {
		edge[i-1][j][DOWN] = false;
		if (edge[i-1][j].count() == 1) {
			add(i-1,j);
		}
	}
	//left right wings
	if (edge[i][j-1][RIGHT] && !edge[i][j+1][LEFT]) {
		edge[i][j-1].reset();
		edge[i][j-1][RIGHT] = true;
		add(i, j-1);
	} else
	if (!edge[i][j-1][RIGHT] && edge[i][j+1][LEFT]) {
		edge[i][j+1].reset();
		edge[i][j+1][LEFT] = true;
		add(i, j+1);
	}
}

void takeDown(int i, int j) {
	if (from[i][j][UP]) {
		bad = true;
		return;
	}
	from[i][j][DOWN] = true;
	assert(from[i][j].count() <= 2);
	if (from[i][j].count() == 2) {
		numBlack--;
	}
	///cerr << "takedown " << i << " " << j << nl;
	assert(grid[i][j] == 'B');
	//down opposing
	if (grid[i+1][j] == 'W' && !seen[i+1][j]) {
		edge[i+1][j][UP] = false;
		if (edge[i+1][j].count() == 1) {
			add(i+1,j);
		}
	}
	//left right wings
	if (edge[i][j-1][RIGHT] && !edge[i][j+1][LEFT]) {
		edge[i][j-1].reset();
		edge[i][j-1][RIGHT] = true;
		add(i, j-1);
	} else
	if (!edge[i][j-1][RIGHT] && edge[i][j+1][LEFT]) {
		edge[i][j+1].reset();
		edge[i][j+1][LEFT] = true;
		add(i, j+1);
	}
}

void takeLeft(int i, int j) {
	if (from[i][j][RIGHT]) {
		bad = true;
		return;
	}
	from[i][j][LEFT] = true;
	assert(from[i][j].count() <= 2);
	if (from[i][j].count() == 2) {
		numBlack--;
	}
	///cerr << "takeleft " << i << " " << j << nl;
	assert(grid[i][j] == 'B');
	//left opposing
	if (grid[i][j-1] == 'W' && !seen[i][j-1]) {
		edge[i][j-1][RIGHT] = false;
		if (edge[i][j-1].count() == 1) {
			add(i,j-1);
		}
	}
	//up down wings
	if (edge[i-1][j][DOWN] && !edge[i+1][j][UP]) {
		edge[i-1][j].reset();
		edge[i-1][j][DOWN] = true;
		add(i-1, j);
	} else if (!edge[i-1][j][DOWN] && edge[i+1][j][UP]) {
		edge[i+1][j].reset();
		edge[i+1][j][UP] = true;
		add(i+1, j);
	}
}

void takeRight(int i, int j) {
	if (from[i][j][LEFT]) {
		bad = true;
		return;
	}
	from[i][j][RIGHT] = true;
	assert(from[i][j].count() <= 2);
	if (from[i][j].count() == 2) {
		numBlack--;
	}
	///cerr << "takeright " << i << " " << j << nl;
	assert(grid[i][j] == 'B');
	//right opposing
	if (grid[i][j+1] == 'W' && !seen[i][j+1]) {
		edge[i][j+1][LEFT] = false;
		if (edge[i][j+1].count() == 1) {
			add(i,j+1);
		}
	}
	//up down wings
	if (edge[i-1][j][DOWN] && !edge[i+1][j][UP]) {
		edge[i-1][j].reset();
		edge[i-1][j][DOWN] = true;
		add(i-1, j);
	} else if (!edge[i-1][j][DOWN] && edge[i+1][j][UP]) {
		edge[i+1][j].reset();
		edge[i+1][j][UP] = true;
		add(i+1, j);
	}
}

void take(int i, int j) {
	///cerr << "taking white square: " << i << ", " << j << nl;
	assert(edge[i][j].count() == 1);
	if (edge[i][j][UP]) {
		takeUp(i-1,j);
	} else if (edge[i][j][DOWN]) {
		takeDown(i+1,j);
	} else if (edge[i][j][LEFT]) {
		takeLeft(i,j-1);
	} else if (edge[i][j][RIGHT]) {
		takeRight(i,j+1);
	}
	edge[i][j].reset();
}

void deal() {
	int n, m; cin >> n >> m;
	memset(edge, 0, sizeof edge);
	memset(grid, 0, sizeof grid);
	memset(seen, 0, sizeof seen);
	ez.clear();
	bad = false;
	memset(from, 0, sizeof from);
	int numWhite = 0;
	numBlack = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> grid[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (grid[i][j] == 'W') {
				edge[i][j][UP] = grid[i-1][j] == 'B';
				edge[i][j][DOWN] = grid[i+1][j] == 'B';
				edge[i][j][LEFT] = grid[i][j-1] == 'B';
				edge[i][j][RIGHT] = grid[i][j+1] == 'B';
				if (edge[i][j].count() == 1) {
					add(i,j);
				}
				numWhite++;
			} else if (grid[i][j] == 'B') {
				numBlack++;
			}
		}
	}
	while(ez.size() && !bad) {
		pii cur = ez.back(); ez.pop_back();
		take(cur.first, cur.second);
		numWhite--;
	}
	if (bad) {
		cout << "NO\n";
		return;
	}

	const int S = 0;
	const int T = 1;
	int wcnt = 0;
	int bcnt = 0;
	Flow::init();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if(edge[i][j].count()) {
				if (edge[i][j][UP]) {
					Flow::add_edge(get(i,j), get(i-1,j));
				}
				if (edge[i][j][DOWN]) {
					Flow::add_edge(get(i,j), get(i+1,j));
				}
				if (edge[i][j][LEFT]) {
					Flow::add_edge(get(i,j), get(i,j-1));
				}
				if (edge[i][j][RIGHT]) {
					Flow::add_edge(get(i,j), get(i,j+1));
				}
				///cerr<<"leftover white " << i << " " << j << nl;
				Flow::add_edge(S, get(i,j));
				wcnt++;
			}
			if(grid[i][j] == 'B') {
				if(from[i][j].count() == 1) {
					///cerr<<"leftover black " << i << " " << j << nl;
					Flow::add_edge(get(i,j), T);
					bcnt++;
				} else if(from[i][j].count() == 0) {
					bad = true;
				}
			}
		}
	}
	if(bad || wcnt != bcnt) {
		cout << "NO" << nl;
		return;
	}
	if(Flow::flow(S, T) == wcnt) {
		cout << "YES" << nl;
	} else {
		cout << "NO" << nl;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int T; cin >> T;
	while(T--) deal();


}

