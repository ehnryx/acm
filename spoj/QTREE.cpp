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

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int L = 14;
const int N = 1e4+1;
vector<int> adj[N];

struct SegTree {
	int n;
	int *segt;
	SegTree(int len) {
		n = 1 << (32-__builtin_clz(len));
		segt = new int[2*n];
		fill(segt, segt+2*n, -1);
	}
	void update(int x, int v) {
		for (segt[x+=n]=v; x>1; x/=2) {
			segt[x/2] = max(segt[x], segt[x^1]);
		}
	}
	int query(int l, int r) {
		int res = -1;
		for (l+=n, r+=n+1; l<r; l/=2, r/=2) {
			if (l&1) res = max(res, segt[(l++)]);
			if (r&1) res = max(res, segt[(--r)]);
		}
		return res;
	}
};

namespace HLD {
  SegTree* segt[N];
  int d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; int dn, cn;
  int dfs(int u, int p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
    for (int x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
  void hld(int u, int p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
    pos[u] = sz[ch[u]=dn]++; int b=-1, c=-1;
    for (int x:adj[u]) if (x!=p && sub[x]>b) { b = sub[c=x]; }
    if (c!=-1) hld(c,u);
    for (int y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
  void build(int r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
    for (int i=0; i<cn; i++) segt[i] = new SegTree(sz[i]); }
  // ASSUME b IS ANCESTOR OF a, modify for insert_node, query_path, query_node
  int query_path(int a, int b) { // please expand this when typing
    int res = -1;
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      res = max(res, segt[ch[a]]->query(0, pos[a]));
      a = par[root[ch[a]]];
    }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      res = max(res, segt[ch[a]]->query(pos[b]+1, pos[a]));
    }
    return res;
  }
	void insert_node(int x, int v) {
		segt[ch[x]]->update(pos[x], v);
	}
}

struct Edge {
	int a, b, c;
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	read(T);

	while (T--) {
		int n;
		read(n);
		for (int i=1; i<=n; i++) {
			adj[i].clear();
		}

		vector<Edge> edges;
		for (int i=1; i<n; i++) {
			int a, b, c;
			read(a); read(b); read(c); 
			adj[a].push_back(b);
			adj[b].push_back(a);
			edges.push_back({a,b,c});
		}
		HLD::build(1);

		for (Edge& e : edges) {
			if (e.a == HLD::par[e.b]) swap(e.a, e.b);
			HLD::insert_node(e.a, e.c);
		}

		for(;;) {
			char s; readchar(s);
			if (s == 'D') {
				readchar(s);
				readchar(s);
				readchar(s);
				break;
			} else if (s == 'Q') {
				readchar(s);
				readchar(s);
				readchar(s);
				readchar(s);
				int a, b;
				read(a); read(b);
				printf("%d\n", HLD::query_path(a,b));
			} else {
				readchar(s);
				readchar(s);
				readchar(s);
				readchar(s);
				readchar(s);
				int a, b;
				read(a); read(b);
				HLD::insert_node(edges[a-1].a, b);
			}
		}
	}

	return 0;
}
