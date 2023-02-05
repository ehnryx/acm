#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "math/ntt.h"

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
  string s;
  cin >> s;
  vector<ll> wilds(n), matcher(n);
  for(int i=0; i<n; i++) {
    if(s[i] == 'V') {
      matcher[i] = 1;
    } else if(s[i] == 'K') {
      matcher[i] = -1;
    } else {
      wilds[i] = 1;
    }
  }
  vector<int> c_wilds(n+1);
  partial_sum(begin(wilds), end(wilds), begin(c_wilds) + 1);

  vector r_wilds(rbegin(wilds), rend(wilds));
  vector r_matcher(rbegin(matcher), rend(matcher));
  wilds = ntt::convolve<MOD>(wilds, r_wilds);
  matcher = ntt::convolve<MOD>(matcher, r_matcher);

  vector<bool> good(n+1);
  good[n] = true;
  for(int shift=1; shift<n; shift++) {
    // n-1 + 0 + shift
    const int zeros = c_wilds[n - shift] + (c_wilds[n] - c_wilds[shift]) - wilds[shift + n-1];
    const int length = n - shift;
    good[shift] = (matcher[shift + n-1] + zeros == length);
  }

  vector<int> ans;
  for(int i=1; i<=n; i++) {
    bool ok = true;
    for(int j=i; j<=n; j+=i) {
      ok &= good[j];
    }
    if(ok) {
      ans.push_back(i);
    }
  }

  cout << size(ans) << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;
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
