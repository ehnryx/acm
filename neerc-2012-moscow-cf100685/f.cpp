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

  vector<int> cap(n+1);
  vector<ld> val(n+1);
  for(int i=1; i<=n; i++) {
    int a;
    cin >> cap[i] >> a;
    val[i] = a;
  }

  vector<vector<int>> adj(n+1);
  vector<int> deg(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    deg[b]++;
  }

  int x, y, z;
  cin >> x >> y >> z;
  val[x] += y;

  queue<int> bfs;
  for(int i=1; i<=n; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    ld extra = max((ld)0, val[u] - cap[u]);
    ld out = extra / adj[u].size();
    val[u] -= extra;
    for(int v : adj[u]) {
      val[v] += out;
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  cout << val[z] << nl;

  return 0;
}
