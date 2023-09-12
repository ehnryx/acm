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
  vector<int> a(n+1), b(m+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  for(int i=1; i<=m; i++) {
    cin >> b[i];
  }

  unordered_map<int, int> cnt;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(a[i] <= b[j]) {
        cnt[b[j] - a[i]]++;
      }
    }
  }

  pair ans(1, 0);
  for(auto [v, c] : cnt) {
    ans = min(ans, pair(-c, v));
  }
  cout << ans.second << nl;
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
