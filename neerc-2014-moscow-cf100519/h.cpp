//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3 + 1;
vector<int> adj[N];
int dist[N][N];

void run_bfs(int s) {
  queue<int> bfs;
  bfs.push(s);
  dist[s][s] = 0;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(dist[s][v] == -1) {
        dist[s][v] = dist[s][u] + 1;
        bfs.push(v);
      }
    }
  }
}

int dsu[N];
int find(int i) {
  if(dsu[i] == 0) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  if(find(i) != find(j)) {
    dsu[find(i)] = find(j);
  }
}

int get(int n, int len) {
  int block = 2*len + 1;
  return (n+block-1) / block;
}

int gsz[N];
bool solve_fixed(int n, int f, int k, int len) {
  memset(gsz, 0, sizeof gsz);
  for(int i=1; i<=n; i++) {
    if(dist[f][i] > len) {
      gsz[find(i)]++;
    }
  }
  int need = 1;
  for(int i=1; i<=n; i++) {
    need += get(gsz[i], len);
  }
  return need <= k;
}

bool solve(int n, int r, int k, int len) {
  for(int i=1; i<=n; i++) {
    if(dist[r][i] <= len && solve_fixed(n, i, k, len)) {
      return true;
    }
  }
  return false;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, k;
  cin >> n >> m >> k;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int root = 0;
  for(int i=1; i<=n; i++) {
    if(adj[i].size() > 2) {
      assert(!root);
      root = i;
    }
  }

  if(!root) {
    int block = (n+k-1) / k;
    cout << block/2 << nl;
    return 0;
  }

  for(int i=1; i<=n; i++) {
    if(i == root) continue;
    for(int j : adj[i]) {
      if(j == root) continue;
      link(i, j);
    }
  }

  memset(dist, -1, sizeof dist);
  for(int i=1; i<=n; i++) {
    run_bfs(i);
  }

  int l = 0;
  int r = n-1;
  while(l < r) {
    int ub = (l+r) / 2;
    if(solve(n, root, k, ub)) {
      r = ub;
    } else {
      l = ub+1;
    }
  }
  cout << r << nl;

  return 0;
}
