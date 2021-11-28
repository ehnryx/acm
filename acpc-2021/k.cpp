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

  int n, k;
  cin >> n >> k;
  vector<int> cnt(k+1);
  for(int i=0; i<n; i++) {
    int a;
    cin >> a;
    cnt[a]++;
  }

  int v = *min_element(begin(cnt)+1, end(cnt));
  vector<int> ans;
  for(int i=1; i<=k; i++) {
    if(cnt[i] == v) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << nl;
  for(int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
