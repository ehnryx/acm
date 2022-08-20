#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ll a, b;
  cin >> a >> b;
  vector<ll> fa, fb;
  for(int i=2; (ll)i*i<=a; i++) {
    while(a % i == 0) {
      fa.push_back(i);
      a /= i;
    }
  }
  if(a) fa.push_back(a);
  for(int i=2; (ll)i*i<=b; i++) {
    while(b % i == 0) {
      fb.push_back(i);
      b /= i;
    }
  }
  if(b) fb.push_back(b);

  if(size(fa) == 1 && size(fb) == 1) {
    cout << (fa == fb ? "no credit" : "full credit") << nl;
    return 0;
  }

  if(unique(begin(fa), end(fa)) != end(fa) || unique(begin(fb), end(fb)) != end(fb)) {
    cout << "no credit" << nl;
    return 0;
  }

  vector<int> s;
  set_intersection(begin(fa), end(fa), begin(fb), end(fb), back_inserter(s));
  if(empty(s)) {
    cout << "partial credit" << nl;
  } else {
    cout << "no credit" << nl;
  }

  return 0;
}
