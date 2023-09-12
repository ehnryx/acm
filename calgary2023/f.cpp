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

struct max2 {
  int big = 0, small = 0;
  void add(int n) {
    if(n > big) {
      small = big;
      big = n;
    } else if(n > small) {
      small = n;
    }
  }
  int get(int n) const {
    if(n == big) return small;
    return big;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  static constexpr int M = 1e6;
  vector<max2> cnt(M);
  auto add = [&](int n) {
    for(int d=2; d*d<=n; d++) {
      int cur = 0;
      while(n % d == 0) {
        n /= d;
        cur++;
      }
      cnt[d].add(cur);
    }
    if(n) {
      cnt[n].add(1);
    }
  };

  auto query = [&](int n) {
    ll decr = 1;
    for(int d=2; d*d<=n; d++) {
      int cur = 0;
      while(n % d == 0) {
        n /= d;
        cur++;
      }
      for(int j = 0; j < cnt[d].big - cnt[d].get(cur); j++) {
        decr *= d;
      }
    }
    if(n) {
      for(int j = 0; j < cnt[n].big - cnt[n].get(1); j++) {
        decr *= n;
      }
    }
    return decr;
  };

  int n;
  cin >> n;
  vector<int> a(n);

  for(int i=0; i<n; i++) {
    cin >> a[i];
    add(a[i]);
  }

  pair<ll, int> ans(numeric_limits<ll>::max(), 0);
  for(int i=0; i<n; i++) {
    ll d = query(a[i]);
    ans = min(ans, pair(d, a[i]));
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
