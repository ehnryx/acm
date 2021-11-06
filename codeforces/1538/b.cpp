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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }
    int sum = accumulate(begin(a), end(a), 0);
    if(sum % n) {
      cout << -1 << nl;
    } else {
      cout << ranges::count_if(a, [=](int x) { return x > sum/n; }) << nl;
    }
  }

  return 0;
}
