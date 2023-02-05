#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  vector<ll> adj(m);
  for(int i=0; i<n; i++) {
    cin >> a[i];
    a[i] -= 1;
    if(i) {
      adj[a[i]] |= 1ll << a[i-1];
      adj[a[i-1]] |= 1ll << a[i];
    }
  }
  adj[a.front()] |= 1ll << a.front();
  adj[a.back()] |= 1ll << a.back();
  vector<int> cost(m);
  for(int i=0; i<m; i++) {
    cin >> cost[i];
  }

  int half = min(20, m);
  vector<int> dp(1<<half); // max independent set
  for(int bm=0; bm<1<<half; bm++) {
    int value = 0;
    bool ok = true;
    for(int i=0; i<half && ok; i++) {
      if(not(bm & 1<<i)) continue;
      ok &= not(adj[i] & 1<<i);
      for(int j=0; j<i && ok; j++) {
        if(not(bm & 1<<j)) continue;
        ok &= not(adj[i] & 1<<j);
      }
      value += cost[i];
      dp[bm] = max(dp[bm], dp[bm ^ 1<<i]);
    }
    if(ok) {
      dp[bm] = max(dp[bm], value);
    }
  }

  int ans = 0;
  for(int bm=0; bm<1<<(m-half); bm++) {
    int other = (1<<half) - 1;
    int value = 0;
    bool ok = true;
    for(int i=0; i<m-half && ok; i++) {
      if(not(bm & 1<<i)) continue;
      ok &= not(adj[i+half] & 1ll<<(i+half));
      for(int j=0; j<i && ok; j++) {
        if(not(bm & 1<<j)) continue;
        ok &= not(adj[i+half] & 1ll<<(j+half));
      }
      value += cost[i+half];
      other &= ~adj[i+half];
    }
    if(ok) {
      ans = max(ans, dp[other] + value);
    }
  }

  cout << accumulate(begin(cost), end(cost), 0) - ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
