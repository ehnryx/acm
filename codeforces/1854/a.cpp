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
  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  vector<pair<int, int>> ans;
  auto update = [&](int i, int j) {
    ans.emplace_back(i, j);
    a[i] += a[j];
  };

  int pos = count_if(begin(a), end(a), [](int v) { return v > 0; });
  int neg = count_if(begin(a), end(a), [](int v) { return v < 0; });
  auto ub = max_element(begin(a), end(a));
  auto lb = min_element(begin(a), end(a));
  if(pos <= 12 and *lb < 0 and abs(*lb * pow(2, 12 - pos)) >= abs(*ub)) {
    for(int i=0; i<12-pos; i++) {
      update(lb - begin(a), lb - begin(a));
    }
    for(int i=1; i<=n; i++) {
      if(a[i] > 0) {
        update(i, lb - begin(a));
      }
    }
    for(int i=n-1; i>=1; i--) {
      update(i, i+1);
    }
  } else {
    for(int i=0; i<12-neg; i++) {
      update(ub - begin(a), ub - begin(a));
    }
    for(int i=1; i<=n; i++) {
      if(a[i] < 0) {
        update(i, ub - begin(a));
      }
    }
    for(int i=2; i<=n; i++) {
      update(i, i-1);
    }
  }

  cout << size(ans) << nl;
  for(auto [i, j] : ans) {
    cout << i << " " << j << nl;
  }
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
