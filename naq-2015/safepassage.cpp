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

  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  struct State {
    int bm, t;
    bool go;
    State(int _bm, int _t, bool _go): bm(_bm), t(_t), go(_go) {}
    bool operator < (const State& o) const {
      return t > o.t;
    }
  };

  priority_queue<State> dijk;
  dijk.emplace((1<<n)-1, 0, true);
  vector vis(1<<n, vector<int>(2, -1));
  while(!dijk.empty()) {
    auto [bm, t, go] = dijk.top();
    dijk.pop();
    if(vis[bm][go] != -1) continue;
    vis[bm][go] = t;
    if(bm == 0) break;
    if(go) {
      for(int i=0; i<n; i++) {
        if(!(bm & 1<<i)) continue;
        for(int j=0; j<n; j++) {
          if(!(bm & 1<<j)) continue;
          dijk.emplace(bm ^ 1<<i ^ 1<<j, t + max(a[i], a[j]), false);
        }
      }
    } else {
      for(int i=0; i<n; i++) {
        if(bm & 1<<i) continue;
        dijk.emplace(bm ^ 1<<i, t + a[i], true);
      }
    }
  }
  cout << vis[0][0] << nl;

  return 0;
}
