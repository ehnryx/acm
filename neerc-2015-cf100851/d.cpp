#include <bits/stdc++.h>
using namespace std;
#define FILENAME "distance"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

struct Triangle {
  int a, b, c;
};

const int N = 5e4+1;
vector<int> adj[N], cent[N];
int cpar[N], trinode[N];
unordered_set<int> sub[N];
int depth[N], sz[N];

void dfs(int u, int par) {
  sz[u] = 1;
  for (int i : adj[u]) {
    if (i != par && depth[i] == -1) {
      dfs(i, u);
      sz[u] += sz[i];
    }
  }
}

void dfsfill(int u, int root, int par=-1) {
  sub[root].insert(u);
  for (int v : adj[u]) {
    if (v != par && depth[v] == -1) {
      dfsfill(v, root, u);
    }
  }
}

void c_decomp(int u, int par=-1, int d=0) {
  // find centroid
  dfs(u, par);
  // walk
  int cur = u;
  while (1) {
    bool bad = 0;
    for (int v : adj[cur]) {
      if (depth[v] == -1 && sz[v] > sz[cur]/2) {
        // reroot
        int vsz = sz[v];
        sz[v] = sz[cur];
        sz[cur] -= vsz;
        cur = v;
        bad = 1;
        break;
      }
    }
    if (!bad) break;
  }
  depth[cur] = d;
  cpar[cur] = par;
  if (par != -1) 
    cent[par].push_back(cur);
  dfsfill(cur, cur);
  for (int v : adj[cur]) {
    if (depth[v] == -1) {
      c_decomp(v, cur, d+1);
    }
  }
}

unordered_map<int,int> dist[N];
void bfs(int s, const unordered_map<int,vector<int>>& g) {
  unordered_set<int> vis;
  queue<int> nxt;
  nxt.push(s);
  vis.insert(s);
  dist[s][s] = 0;
  while (!nxt.empty()) {
    int u = nxt.front();
    nxt.pop();
    ////cerr << s << ": " << "g.at " << u << endl;
    for (int x : g.at(u)) {
      if (!vis.count(x)) {
        vis.insert(x);
        nxt.push(x);
        dist[s][x] = dist[s][u] + 1;
        //cerr << "add " << s << " <- " << x << " " << dist[s][u] << endl;
      }
    }
  }
}

vector<Triangle> tris;
void build(int root, const unordered_map<int,vector<int>>& graph) {
  unordered_set<int> nodes;
  for (int it : sub[root]) {
    nodes.insert(tris[it].a);
    nodes.insert(tris[it].b);
    nodes.insert(tris[it].c);
  }
  ////cerr << "root: " << root << ": " << sub[root].size() << endl;
  //assert(sub[root].count(root));

  unordered_map<int,vector<int>> ng;
  for (int u : nodes) {
    trinode[u] = root;
    ////cerr << "graph.at " << u << endl;
    for (int v : graph.at(u)) {
      if (nodes.count(v)) {
        ng[u].push_back(v);
      }
    }
  }
  bfs(tris[root].a, ng);
  bfs(tris[root].b, ng);
  bfs(tris[root].c, ng);

  for (int x : cent[root]) {
    build(x, ng);
  }
}

int solve(int u, int v) {
  //int aa=trinode[u], bb=trinode[v];
  int a=trinode[u], b=trinode[v];
  if (depth[a] < depth[b]) swap(a,b);
  while (depth[a] > depth[b]) {
    a = cpar[a];
  }
  while (a != b) {
    a = cpar[a];
    b = cpar[b];
  }
  const auto& t = tris[a];
  //assert(sub[a].count(aa) && sub[a].count(bb));
  assert(dist[t.a].count(u) && dist[t.a].count(v));
  assert(dist[t.b].count(u) && dist[t.b].count(v));
  assert(dist[t.c].count(u) && dist[t.c].count(v));
  return min(dist[t.a][u]+dist[t.a][v],
         min(dist[t.b][u]+dist[t.b][v],
             dist[t.c][u]+dist[t.c][v]));
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  unordered_map<int,vector<int>> tree;

  for (int i=0; i<n-3; i++) {
    int a, b;
    cin >> a >> b;
    tree[a].push_back(b);
    tree[b].push_back(a);
  }
  for (int i=1; i<=n; i++) {
    int j = (i==n ? 1 : i+1);
    tree[i].push_back(j);
    tree[j].push_back(i);
  }

  map<pii, vector<int>> edges;
  auto add_edge = [&] (int a, int b, int id) {
    edges[pii(min(a,b),max(a,b))].push_back(id);
  };

  for (int i=1; i<=n; i++) {
    sort(tree[i].begin(), tree[i].end());
    for (int j=0; j<tree[i].size()-1; j++) {
      if (tree[i][j] < i) continue;
      tris.push_back({i,tree[i][j],tree[i][j+1]});
      add_edge(i,tree[i][j],tris.size()-1);
      add_edge(i,tree[i][j+1],tris.size()-1);
      add_edge(tree[i][j],tree[i][j+1],tris.size()-1);
    }
  }

  for (const auto& it : edges) {
    if (it.second.size() == 2) {
      adj[it.second[0]].push_back(it.second[1]);
      adj[it.second[1]].push_back(it.second[0]);
    } else {
      //assert(it.second.size() == 1);
    }
  }


  ////cerr << "TRIANGLES: " << nl; for (int i=0; i<tris.size(); i++) {
  ////cerr << i << ": " << tris[i].a << " " << tris[i].b << " " << tris[i].c << nl; }
  ////cerr << nl;

  //cerr << "GRAPH: " << nl; for (int i=0; i<tris.size(); i++) {
  //cerr << i << ": "; for (int j:adj[i]) //cerr << j << " ";
  //cerr << nl; }
  //cerr << nl;

  memset(depth, -1, sizeof depth);
  memset(cpar, -1, sizeof cpar);
  c_decomp(0);
  //for (int i = 0; i < tris.size(); i++) if (depth[i] == -1) assert(0);

  //cerr << "CPAR: " << nl; for (int i=0; i<tris.size(); i++) {
  //cerr << i << ": " << cpar[i] << nl; }
  //cerr << nl;

  //cerr << "DEPTH: " << nl; for (int i=0; i<tris.size(); i++) {
  //cerr << i << ": " << depth[i] << nl; }
  //cerr << nl;

  ////cerr << "SUB: " << nl; for (int i=0; i<tris.size(); i++) {
  ////cerr << i << ": "; for (int j:sub[i]) ////cerr << j << " ";
  ////cerr << nl; }
  ////cerr << nl;

  int root = -1;
  int m = tris.size();
  for (int i=0; i<m; i++) {
    if (cpar[i] == -1) {
      root = i;
      break;
    }
  }
  //assert(root != -1);
  build(root, tree);

  ////cerr << "DISTS: " << nl; for (int i=1; i<=n; i++) {
  ////cerr << i << ": "; for (pii j:dist[i]) //cerr << j.first << ',' << j.second << "  ";
  ////cerr << nl; }
  ////cerr << nl;

  ////cerr << "TRINODE: " << nl; for (int i=1; i<=n; i++) {
  ////cerr << i << ": " << trinode[i] << nl; }
  ////cerr << nl;

  int q;
  cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << solve(a,b) << nl;
  }

  return 0;
}
