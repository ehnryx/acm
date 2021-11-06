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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<ld> a;
    for(int i=0; i<n; i++) {
      int m;
      cin >> m;
      int cur = 0;
      for(int j=0; j<m; j++) {
        int v;
        cin >> v;
        cur += v;
      }
      a.push_back(cur);
    }
    sort(begin(a), end(a));
    partial_sum(begin(a), end(a), begin(a));
    cout << accumulate(begin(a), end(a), (ld)0) / n << nl;
  }

  return 0;
}
