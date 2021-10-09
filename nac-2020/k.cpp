//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') ;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
// END MAGIC IO

typedef long long ll;
#define nl '\n'

const int N = 2e5 + 1;
vector<int> adj[N];
vector<pair<int,int>> path[N];
int sz[N], depth[N];
int A[N], B[N], C[N];

bool vis[N];
int dsu[N], anc[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  if(find(i) != find(j)) {
    dsu[find(i)] = find(j);
  }
}

int build(int u, int p) {
  depth[u] = depth[p] + 1;
  anc[u] = u;
  sz[u] = 1;
  for(int v : adj[u]) {
    if(v != p) {
      sz[u] += build(v, u);
      link(u, v);
      anc[find(u)] = u;
    }
  }
  vis[u] = true;
  for(auto [v, i] : path[u]) {
    if(vis[v]) {
      C[i] = anc[find(v)];
    }
  }
  return sz[u];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m;
  read(n); read(m);
  for(int i=1; i<n; i++) {
    int a, b;
    read(a); read(b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for(int i=0; i<m; i++) {
    read(A[i]); read(B[i]);
    path[A[i]].emplace_back(B[i], i);
    path[B[i]].emplace_back(A[i], i);
  }

  memset(dsu, -1, sizeof dsu);
  build(1, 0);

  for(int i=0; i<m; i++) {
    int k = depth[A[i]] + depth[B[i]] - 2*depth[C[i]];
    cout << n - k - 1 + (ll)(k+1)*(k+2)/2 << nl;
  }

  return 0;
}
