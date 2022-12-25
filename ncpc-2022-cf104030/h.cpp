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
  vector<ll> h(n);
  for(int i=0; i<n; i++) {
    cin >> h[i];
  }
  h.resize(distance(begin(h), unique(begin(h), end(h))));
  n = size(h);

  auto solve = [&](int m) {
    if(h[m] < h[m-1] or h[m] < h[m+1]) return 0ll;
    int i = 1;
    while(m-i>=0 and m+i<n) {
      if(h[m-i] > h[m-i+1] or h[m+i] > h[m+i-1]) {
        break;
      }
      i++;
    }
    ll left = h[m] - h[m-i + 1];
    ll right = h[m] - h[m+i - 1];
    for(int j=i; m-j>=0 and h[m-j] < h[m-j+1]; j++) {
      left = h[m] - h[m-j];
    }
    for(int j=i; m+j<n and h[m+j] < h[m+j-1]; j++) {
      right = h[m] - h[m+j];
    }
    return min(left, right);
  };

  ll ans = 0;
  for(int i=1; i+1<n; i++) {
    ans = max(ans, solve(i));
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
