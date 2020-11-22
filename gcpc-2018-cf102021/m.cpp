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

const int N = 500 + 2;
int g[N][N];

int dsu[N*N];
unordered_set<int> todo[N*N];
int find(int i) {
  if(dsu[i] == 0) return i;
  return dsu[i] = find(dsu[i]);
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

  int n, m, q;
  cin >> n >> m >> q;

  vector<tuple<int,int,int>> edges;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      if(i > 1) {
        edges.emplace_back(max(g[i][j], g[i-1][j]), i*N + j, (i-1)*N + j);
      }
      if(j > 1) {
        edges.emplace_back(max(g[i][j], g[i][j-1]), i*N + j, i*N + (j-1));
      }
    }
  }
  sort(edges.begin(), edges.end());

  vector<int> ans(q, -1);
  for(int i=0; i<q; i++) {
    int a, b, s, t;
    cin >> a >> b >> s >> t;
    int u = a*N + b;
    int v = s*N + t;
    if(u == v) {
      ans[i] = g[a][b];
    } else {
      todo[u].insert(i);
      todo[v].insert(i);
    }
  }

  for(auto [c, a, b] : edges) {
    a = find(a);
    b = find(b);
    if(a == b) continue;
    if(todo[a].size() > todo[b].size()) {
      swap(a, b);
    }

    for(int i : todo[a]) {
      if(todo[b].count(i)) {
        todo[b].erase(i);
        ans[i] = c;
      } else {
        todo[b].insert(i);
      }
    }
    dsu[a] = b;
  }

  for(int i=0; i<q; i++) {
    assert(ans[i] >= 0);
    cout << ans[i] << nl;
  }

  return 0;
}
