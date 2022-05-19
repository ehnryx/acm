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
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  int sum = accumulate(begin(a), end(a), 0);
  vector<int> ans;
  for(int i=0; i<n; i++) {
    ans.push_back(sum - a[i]);
  }
  sort(begin(ans), end(ans));
  ans.resize(unique(begin(ans), end(ans)) - begin(ans));

  cout << ans.size() << nl;
  for(int v : ans) {
    cout << v << " ";
  }
  cout << nl;

  return 0;
}
