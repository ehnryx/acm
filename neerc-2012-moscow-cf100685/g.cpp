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

const int L = 17;
const int N = 1e5 + 1;
vector<pair<int,int>> adj[N];
int anc[N][L], depth[N];
int st[2*N], pos[N];

int sid = 0;
void build(int u, int p) {
  depth[u] = depth[p] + 1;
  anc[u][0] = p;
  for(int j=1; j<L; j++) {
    anc[u][j] = anc[anc[u][j-1]][j-1];
  }
  pos[u] = sid;
  for(auto [v, c] : adj[u]) {
    if(v == p) continue;
    st[++sid] = c;
    build(v, u);
    st[++sid] = -c;
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

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].emplace_back(b, 1);
    adj[b].emplace_back(a, -1);
  }
  build(1, 0);
  partial_sum(st, st+sid+1, st);

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    int len = depth[a] + depth[b] - 2*depth[lca(a, b)];
    if(len == st[pos[b]] - st[pos[a]]) {
      cout << "Yes" << nl;
    } else {
      cout << "No" << nl;
    }
  }

  return 0;
}
