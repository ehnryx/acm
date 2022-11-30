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
  int n;
  cin >> n;
  vector<int> a(n+4);
  for(int i=0; i<4; i++) {
    cin >> a[i];
  }
  int sj = min(10, a[0]) + min(10, a[1]);
  int sm = min(10, a[2]) + min(10, a[3]);
  for(int i=0; i<n; i++) {
    cin >> a[i+4];
    sj += min(10, a[i+4]);
    sm += min(10, a[i+4]);
  }

  if(sj > sm) {
    int lb = 23 - sj + 1;
    int ub = 23 - sm + 1;
    if(lb <= 10) {
      for(int i=lb; i<=13; i++) {
        if(min(10, i) < ub and count(begin(a), end(a), i) < 4) {
          cout << i << nl;
          return;
        }
      }
    }
  } else {
    int need = 23 - sm;
    if(need <= 10) {
      for(int i=need; i<=13; i++) {
        if(min(10, i) == need and count(begin(a), end(a), i) < 4) {
          cout << i << nl;
          return;
        }
      }
    }
  }

  cout << -1 << nl;
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
