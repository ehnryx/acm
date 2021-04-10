#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
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
//typedef long double ld;
typedef double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  vector<int> score(n+m+1);
  for(int i=1; i<=n; i++) {
    cin >> score[i];
  }
  vector<vector<pair<int,int>>> adj(n+m+1);
  vector p(n+m+1, vector<ld>(2));
  for(int i=1; i<=m; i++) {
    int li, ri;
    cin >> p[i+n][0] >> p[i+n][1] >> li >> ri;
    adj[li].emplace_back(i+n, 0);
    adj[ri].emplace_back(i+n, 1);
  }

  function<ld(ld)> calc = [=](ld s) {
    vector<int> deg(n+m+1);
    vector<ld> val(n+m+1);
    for(int i=1; i<=n; i++) {
      val[i] = score[i];
    }
    for(int i=1; i<=m; i++) {
      deg[i+n] = 2;
    }

    queue<int> bfs;
    for(int i=1; i<=n+m; i++) {
      if(deg[i] == 0) {
        bfs.push(i);
      }
    }
    while(!bfs.empty()) {
      int u = bfs.front();
      bfs.pop();
      if(u > n) val[u] += (1 - p[u][0] - p[u][1]) * s;
      for(auto [v, t] : adj[u]) {
        val[v] += p[v][t] * val[u];
        if(--deg[v] == 0) {
          bfs.push(v);
        }
      }
    }

    ld res = 0;
    for(int i=1; i<=n+m; i++) {
      if(adj[i].empty()) {
        res = max(res, val[i]);
      }
    }
    return res;
  };

  ld l = 0;
  ld r = *max_element(score.begin(), score.end());
  for(int bs=0; bs<42; bs++) {
    ld guess = (l + r) / 2;
    ld res = calc(guess);
    if(res < guess) {
      r = guess;
    } else {
      l = guess;
    }
  }

  cout << calc((l+r)/2) << nl;

  return 0;
}
