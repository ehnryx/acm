#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  nd_array<char, 2> g(n+2, n+2);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> g(i, j);
      g(i, j) -= '0';
    }
  }
  int ans = 0;
  nd_array<char, 2> add(n+2, n+2), left(n+2, n+2), right(n+2, n+2), down(n+2, n+2);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(g(i, j) ^ add(i, j)) {
        ans++;
        left(i, j) ^= 1;
        right(i, j) ^= 1;
        down(i, j) ^= 1;
      }

      left(i+1, j-1) ^= left(i, j);
      down(i+1, j-1) ^= left(i, j);
      down(i+1, j) ^= down(i, j);
      right(i+1, j+1) ^= right(i, j);
      down(i+1, j+1) ^= right(i, j);

      add(i+1, j-1) ^= left(i, j);
      add(i+1, j) ^= down(i, j);
      add(i+1, j+1) ^= right(i, j);
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
