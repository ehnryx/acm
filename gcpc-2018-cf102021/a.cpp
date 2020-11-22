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

const int N = (1e3 + 1) * (1e3 + 1) + 1;
const int L = 20;
vector<int> adj[N];
int anc[N][L];
int depth[N];

void build(int u, int p = 0) {
  depth[u] = depth[p] + 1;
  anc[u][0] = p;
  for(int j=1; j<L; j++) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  for(int v : adj[u]) {
    if(v != p) {
      build(v, u);
    }
  }
}

int lca(int a, int b) {
  if(depth[a] < depth[b]) swap(a, b);
  for(int j=L-1; j>=0; j--) {
    if(depth[anc[a][j]] >= depth[b]) {
      a = anc[a][j];
    }
  }
  if(a == b) return a;
  for(int j=L-1; j>=0; j--) {
    if(anc[a][j] != anc[b][j]) {
      a = anc[a][j];
      b = anc[b][j];
    }
  }
  return anc[a][0];
}

int get_dist(int a, int b) {
  int c = lca(a, b);
  return depth[a] + depth[b] - 2 * depth[c];
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

  int n, m;
  cin >> n >> m;

  string line;
  getline(cin, line);
  getline(cin, line);

  for(int i=1; i<=n; i++) {
    getline(cin, line);
    for(int j=1; j<m; j++) {
      if(isspace(line[2*j])) {
        adj[i*m + j].push_back(i*m + j-1);
        adj[i*m + j-1].push_back(i*m + j);
      }
    }
    for(int j=0; j<m; j++) {
      if(isspace(line[2*j + 1])) {
        adj[i*m + j].push_back((i+1)*m + j);
        adj[(i+1)*m + j].push_back(i*m + j);
      }
    }
  }
  build(m);

  int k;
  cin >> k;
  ll ans = 0;
  for(int i=0, p=-1; i<k; i++) {
    int a, b;
    cin >> a >> b;
    int u = a*m + (b-1);
    if(p != -1) {
      ans += get_dist(p, u);
    }
    p = u;
  }
  cout << ans << nl;

  return 0;
}
