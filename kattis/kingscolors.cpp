#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k;
  cin >> n >> k;
  vector<vector<int>> adj(n);
  for(int i=1; i<n; i++) {
    int parent;
    cin >> parent;
    adj[parent].push_back(i);
  }

  vector<Int> val(k+1);
  for(int i=2; i<=k; i++) {
    auto f = [i, &adj](auto&& self, int u) -> Int {
      Int res = 1;
      for(int v : adj[u]) {
        // i-1 choices to colour v
        res *= Int(i-1) * self(self, v);
      }
      return res;
    };
    val[i] = Int(i) * f(f, 0);
  }

  vector ncr(k+1, vector<Int>(k+1));
  for(int i=0; i<=k; i++) {
    ncr[i][i] = ncr[i][0] = Int(1);
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }
  auto choose = [&ncr](int N, int R) -> Int {
    if(R<0 or N<R) return Int(0);
    return ncr[N][R];
  };

  Int ans = val[k];
  for(int i=1; i<=k; i++) {
    int s = i % 2 ? -1 : 1;
    ans += val[k-i] * choose(k, i) * Int(s);
  }
  cout << ans << nl;
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
