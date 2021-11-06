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

  static const int M = 20'000 + 1;
  vector<bool> good(M);
  good[0] = true;
  for(int i=2; i<M; i++) {
    bool prime = true;
    for(int j=2; j*j<=i; j++) {
      if(i % j == 0) {
        prime = false;
        break;
      }
    }
    good[i] = prime;
  }

  int T;
  cin >> T;
  while(T--) {
    int n, d;
    cin >> n >> d;
    ld sum = 0;
    pt cur(0, 0);
    int val = 0;
    int ans = 0;
    for(int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      sum += abs(pt(x, y) - cur);
      val += (sum < d + EPS);
      if(good[val]) ans = val;
      cur = pt(x, y);
    }
    cout << ans << nl;
  }

  return 0;
}
