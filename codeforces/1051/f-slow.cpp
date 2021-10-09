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

struct Edge {
  int pre, id;
  ll dist;
  Edge(int p, int i, ll d): pre(p), id(i), dist(d) {}
};

const int N = 1e5+1;
const int L = 18;

int root[N];
int find(int i) {
  if (root[i] == -1) return i;
  return root[i] = find(root[i]);
}
bool link(int i, int j) { 
  if (find(i) != find(j)) {
    root[find(i)] = find(j);
    return true;
  }
  return false;
}

vector<Edge> adj[N];
int depth[N];
int lca[N][L];
ll len[N][L];

void build(int cur, int par, ll dist) {
  depth[cur] = depth[par]+1;
  if (par) {
    lca[cur][0] = par;
    len[cur][0] = dist;
  }
  for (int i=1; 1<<i<depth[cur]; i++) {
    lca[cur][i] = lca[lca[cur][i-1]][i-1];
    len[cur][i] = len[lca[cur][i-1]][i-1] + len[cur][i-1];
  }
  for (const Edge& e : adj[cur]) {
    if (e.id != par) {
      build(e.id, cur, e.dist);
    }
  }
}

ll query(int a, int b) {
  ll res = 0;
  if (depth[a] < depth[b]) swap(a,b);
  int d = depth[a]-depth[b];
  for (int i=0; d>0; i++,d/=2) {
    if (d&1) {
      res += len[a][i];
      a = lca[a][i];
    }
  }
  if (a==b) return res;

  for (int i=31-__builtin_clz(depth[a]); i>=0; i--) {
    if (1<<i < depth[a] && lca[a][i] != lca[b][i]) {
      res += len[a][i]+len[b][i];
      a = lca[a][i];
      b = lca[b][i];
    }
  }
  return res + len[a][0]+len[b][0];
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  memset(lca, -1, sizeof lca);
  memset(root, -1, sizeof root);

  int n, m, a, b, c;
  cin >> n >> m;

  vector<Edge> edges;
  for (int i=0; i<m; i++) {
    cin >> a >> b >> c;
    edges.push_back(Edge(a,b,c));
  }

  unordered_set<int> seen;
  vector<Edge> cross;
  for (const Edge& e : edges) {
    if (link(e.pre, e.id)) {
      adj[e.pre].push_back(Edge(e.pre, e.id, e.dist));
      adj[e.id].push_back(Edge(e.id, e.pre, e.dist));
    } else {
      cross.push_back(e);
      seen.insert(e.pre);
      seen.insert(e.id);
    }
  }
  build(1, 0, 0);

  vector<int> node;
  unordered_map<int,int> nid;
  for (int i : seen) {
    nid[i] = node.size();
    node.push_back(i);
  }
  m = node.size();

  ll trivial[m][m];
  memset(trivial, INF, sizeof trivial);
  for (const Edge& e : cross) {
    trivial[nid[e.pre]][nid[e.id]] = trivial[nid[e.id]][nid[e.pre]] = e.dist;
  }
  for (int i=0; i<m; i++) {
    for (int j=0; j<m; j++) {
      trivial[i][j] = min(trivial[i][j], query(node[i],node[j]));
    }
  }
  for (int k=0; k<m; k++) {
    for (int i=0; i<m; i++) {
      for (int j=0; j<m; j++) {
        trivial[i][j] = min(trivial[i][j], trivial[i][k]+trivial[k][j]);
      }
    }
  }

  int q;
  cin >> q;
  while (q--) {
    cin >> a >> b;
    ll ans = query(a, b);
    for (int i=0; i<m; i++) {
      for (int j=0; j<m; j++) {
        ans = min(ans, query(a,node[i])+query(b,node[j])+trivial[i][j]);
      }
    }
    cout << ans << nl;
  }

  return 0;
}
