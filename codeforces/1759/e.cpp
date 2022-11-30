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


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, h;
  cin >> n >> h;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a));

  int best = 0;
  vector<int> order = { 2, 2, 3 };
  do {
    ll hv = h;
    int at = 0;
    int ans = 0;
    for(int x : a) {
      while(x >= hv and at < 3) {
        hv *= order[at++];
      }
      if(x >= hv) {
        break;
      }
      hv += x / 2;
      ans++;
    }
    best = max(best, ans);
  } while(next_permutation(begin(order), end(order)));

  cout << best << nl;
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
