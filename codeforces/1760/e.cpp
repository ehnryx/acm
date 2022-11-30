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

ll solve(const vector<int>& a) {
  int ones = 0;
  ll res = 0;
  for(int i=0; i<size(a); i++) {
    if(a[i] == 0) {
      res += ones;
    } else {
      ones++;
    }
  }
  return res;
}

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  auto b = a;
  for(int i=0; i<n; i++) {
    if(b[i] == 0) {
      b[i] = 1;
      break;
    }
  }
  auto c = a;
  for(int i=n-1; i>=0; i--) {
    if(c[i] == 1) {
      c[i] = 0;
      break;
    }
  }
  cout << max(solve(b), solve(c)) << nl;
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
