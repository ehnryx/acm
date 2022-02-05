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

  const int M = 1e3 + 1;

  int n, m;
  cin >> n >> m;
  vector<bitset<M>> bs(n);
  for(int i=0; i<n; i++) {
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      int v;
      cin >> v;
      bs[i].set(v);
    }
  }

  int ans = 0;
  bitset<M> cur;
  for(int i=0; i<m; i++) {
    int v;
    cin >> v;
    cur.set(v);
    bool ok = false;
    for(int j=0; j<n; j++) {
      if((bs[j] & cur) == cur) {
        ok = true;
        break;
      }
    }
    if(!ok) {
      ans++;
      cur.reset();
      cur.set(v);
    }
  }
  cout << ans << nl;

  return 0;
}
