%:include <bits/stdc++.h>
using namespace std;

%:include "../../../lca/misc/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int prime_factor(int n) {
  int res = 0;
  for(int i=2; i*i<=n; i++) {
    while(n % i == 0) {
      n /= i;
      res++;
    }
  }
  return res + (n > 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int a, b, k;
    cin >> a >> b >> k;
    if(k == 1) {
      cout << (min(a, b) == gcd(a, b) && a != b ? "YES" : "NO") << nl;
    } else {
      cout << (prime_factor(a) + prime_factor(b) >= k ? "YES" : "NO") << nl;
    }
  }

  return 0;
}
