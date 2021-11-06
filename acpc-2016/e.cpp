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
  for(int tt=1; tt<=T; tt++) {
    cout << "Test " << tt << nl;
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for(int i=0; i<n; i++) {
      cin >> g[i];
    }
    reverse(begin(g), end(g));
    for(string& s : g) {
      reverse(begin(s), end(s));
      cout << s << nl;
    }
  }

  return 0;
}
