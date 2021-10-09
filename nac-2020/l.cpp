#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const vector<int> di = { 1, -1, 0, 0 };
const vector<int> dj = { 0, 0, 1, -1 };

const int N = 500 + 2;
const int M = 2*N*N;
vector<int> adj[M];
char g[N][N];
int idx[N][N];
int gid;

int go(int n, int m, int i, int j, int d) {
  if(i<1) return go(n, m, i+1, j, 0);
  if(i>n) return go(n, m, i-1, j, 1);
  if(j<1) return go(n, m, i, j+1, 2);
  if(j>m) return go(n, m, i, j-1, 3);
  if(g[i][j] == '#') return 0;
  if(g[i][j] == '.') return go(n, m, i+di[d], j+dj[d], d);
  if(g[i][j] == '/') {
    d = 3 - d;
    return go(n, m, i+di[d], j+dj[d], d);
  } else if(g[i][j] == '\\') {
    d = (d+2) % 4;
    return go(n, m, i+di[d], j+dj[d], d);
  } else {
    return idx[i][j] + (d<2 ? 0 : gid);
  }
}

int dsu[M], cost[M], bad[M];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if(i == j) return;
  cost[i] += cost[j];
  bad[i] |= bad[j];
  dsu[j] = i;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  memset(dsu, -1, sizeof dsu);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      if(g[i][j] == 'V' || g[i][j] == 'H') {
        idx[i][j] = ++gid;
      }
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == 'V' || g[i][j] == 'H') {
        int s = idx[i][j];
        adj[s].push_back(go(n, m, i+di[0], j+dj[0], 0));
        adj[s].push_back(go(n, m, i+di[1], j+dj[1], 1));
        adj[s+gid].push_back(go(n, m, i+di[2], j+dj[2], 2));
        adj[s+gid].push_back(go(n, m, i+di[3], j+dj[3], 3));
        for(int k : adj[s]) {
          if(k == 0) bad[s] = true;
        }
        for(int k : adj[s+gid]) {
          if(k == 0) bad[s+gid] = true;
        }
        if(g[i][j] == 'V') {
          cost[s+gid] = 1;
        } else {
          cost[s] = 1;
        }
      }
    }
  }

  for(int i=1; i<=gid; i++) {
    for(int j : adj[i]) {
      if(j == 0) continue;
      link(i, j);
      link(i+gid, (j>gid ? j-gid : j+gid));
    }
    for(int j : adj[i+gid]) {
      if(j == 0) continue;
      link(i+gid, j);
      link(i, (j>gid ? j-gid : j+gid));
    }
  }

  int ans = 0;
  for(int i=1; i<=gid; i++) {
    if(find(i) == find(i+gid)) {
      cout << -1 << nl;
      return 0;
    }
    if(find(i) == i) {
      assert(find(i+gid) == i+gid);
      int cur = 1e9 + 7;
      if(!bad[i]) cur = min(cur, cost[i]);
      if(!bad[i+gid]) cur = min(cur, cost[i+gid]);
      if(cur > 1e9 + 2) {
        cout << -1 << nl;
        return 0;
      }
      ans += cur;
    }
  }
  cout << ans << nl;

  return 0;
}

