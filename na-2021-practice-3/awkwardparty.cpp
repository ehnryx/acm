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
  int ans = n;
  map<int, int> last;
  for(int i=1; i<=n; i++) {
    int v;
    cin >> v;
    if(last[v]) {
      ans = min(ans, i - last[v]);
    }
    last[v] = i;
  }
  cout << ans << nl;

  return 0;
}
