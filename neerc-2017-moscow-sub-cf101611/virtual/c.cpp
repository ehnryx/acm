#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 1e5+10;
const int X = 1e6, Y = 20;

int n;
vector<int> adj[N];
vector<int> sol[Y];

vector<int> tree;
void dfs(int u, int par) {
  //cerr << "at " << u << " par = " << par << nl;
  tree.push_back(u);
  for (int i : adj[u]) {
    //cerr << "neigh " << i << nl;
    if (i != par) dfs(i, u);
  }
}

int deg[N];

int centroid(int u, int par) {
  tree.clear();
  dfs(u, par);
  if (tree.size() == 1) return u;
  queue<int> q;
  for (int i : tree) {
    deg[i] = adj[i].size();
    if (i == u && u != 0) deg[i]--;
    if (deg[i] == 1) q.push(i);
  }
  int ans = -1;
  while (!q.empty()) {
    ans = q.front(); q.pop();
    for (int i : adj[ans]) {
      if (--deg[i] == 1) {
        q.push(i);
      }
    }
  }
  return ans;
}

int p[N];
void dfs2(int u, int par=-1) {
  for (int i : adj[u]) {
    if (i != par) {
      p[i] = u;
      dfs2(i, u);
    }
  }
}

void solve(int u, int level, int par=-1) {
  assert(level < Y);
  sol[level].push_back(u);
  int c = centroid(u, par);
  //cerr << u << " " << level << " = " << c << nl;
  vector<int> path;
  while (c != u) {
    path.push_back(c);
    c = p[c];
  }
  reverse(path.begin(), path.end());
  for (int i : adj[u]) {
    if (i != par && (path.empty() || i != path[0])) {
      solve(i, level+1, u);
    }
  }
  for (int i = 0; i < path.size(); i++) {
    sol[level].push_back(path[i]);
    for (int j : adj[path[i]]) {
      if (j != p[path[i]] && (i+1 == path.size() || j != path[i+1])) {
        solve(j, level+1, path[i]);
      }
    }
  }
}

int x[N], y[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  memset(p, -1, sizeof p);
  cin >> n;
  for (int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v; u--; v--;
    //cerr << u << " " << v << nl;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  /*
  for (int i = 0; i < n; i++) {
    cerr << i << ": ";
    for (int j : adj[i]) cerr << j << " "; cerr << nl;
  }*/
  dfs2(0);
  solve(0, 0);
  for (int i = 0; i < Y; i++) {
    for (int j = 0; j < sol[i].size(); j++) {
      x[sol[i][j]] = j;
      y[sol[i][j]] = i;
    }
  }
  for (int i = 0; i < n; i++) {
    cout << x[i]+1 << " " << y[i]+1 << nl;
  }

  return 0;
}
