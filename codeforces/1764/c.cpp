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
  map<int, int> cnt;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
    cnt[a[i]]++;
  }
  sort(begin(a), end(a));

  ll ans = n/2;
  int smaller = 0;
  for(int i=0; i<n; i++) {
    ll left = i - smaller;
    ll right = cnt[a[i]] - left;
    ll cur = (i - left) * (n - i) + left * (n - i - right);
    ans = max(ans, cur);
    if(i+1 == n or a[i] != a[i+1]) {
      smaller += cnt[a[i]];
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
