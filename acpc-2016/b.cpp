#include <bits/stdc++.h>
using namespace std;

#include "../../lca/misc/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1e4 + 1;
int h[N], e[N];
ll all[N], half[N];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n, d;
    cin >> n >> d;
    //vector<int> h(n+1), e(n+1);
    for(int i=1; i<=n; i++) {
      cin >> h[i];
    }
    for(int i=1; i<=n; i++) {
      cin >> e[i];
    }

    //vector<ll> all(n+1), half(n+1);
    for(int i=1; i<=n; i++) {
      half[i] = min(
          (h[i] + d-1) / d + all[i-1],
          (max(0, h[i] - e[i-1]) + d-1) / d + half[i-1]);
      if(i < n) {
        all[i] = min(
            (max(0, h[i] - e[i+1]) + d-1) / d + all[i-1],
            (max(0, h[i] - e[i+1] - e[i-1]) + d-1) / d + half[i-1]);
      }
      all[i] = min(all[i], half[i]);
    }
    cout << half[n] << nl;
  }

  return 0;
}
