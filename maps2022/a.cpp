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
  int n, s, m;
  cin >> n >> s >> m;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  vector<bool> vis(n);
  int at = s;
  int ans = 0;
  while(true) {
    if(a[at] == m) {
      cout << "magic" << nl;
      break;
    }
    vis[at] = true;
    ans++;
    at += a[at];
    if(at < 1) {
      cout << "left" << nl;
      break;
    }
    if(at > n) {
      cout << "right" << nl;
      break;
    }
    if(vis[at]) {
      cout << "cycle" << nl;
      break;
    }
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
