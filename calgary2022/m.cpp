#include <bits/stdc++.h>
using namespace std;

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

  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  for(int k=1; 2*k<=n; k++) {
    bool ok = true;
    for(int i=2; i*k<=n && ok; i++) {
      ok &= (a[i*k] > a[(i-1)*k]);
    }
    if(ok) {
      cout << k << nl;
      return 0;
    }
  }

  cout << "ABORT!" << nl;

  return 0;
}
