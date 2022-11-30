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

int count(int n, int d) {
  int cnt = 0;
  while(n % d == 0) {
    n /= d;
    cnt++;
  }
  return cnt;
}

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;

  int tn = count(n, 2);
  int fn = count(n, 5);
  ll base = 1;
  for(int i=tn; i<fn and base*2 <= m; i++) {
    base *= 2;
  }
  for(int i=fn; i<tn and base*5 <= m; i++) {
    base *= 5;
  }
  while(base*10 <= m) {
    base *= 10;
  }
  cout << n * (m / base * base) << nl;
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
