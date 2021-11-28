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

  static const int N = 20;
  vector<char> ans(N, '?');
  for(int k=0; k<N; k++) {
    int len = 1<<k;
    if(len < n) {
      if(a[len] == a[len-1]) {
        ans[k] = 'x';
      } else {
        ans[k] = (a[len] < a[len-1] ? 'A' : 'B');
        for(int i=0; i<n; i++) {
          if(((i >> k) & 1) == (ans[k] == 'B')) {
            a[i] -= 1;
          }
        }
      }
    }
  }

  sort(begin(a), end(a));
  a.resize(unique(begin(a), end(a)) - begin(a));
  assert(a.size() == 1);
  if(a[0] == count(begin(ans), end(ans), '?')) {
    for(int k=0; k<N; k++) {
      if(ans[k] == '?') ans[k] = 'A';
    }
  }

  for(int k=0; k<N; k++) {
    cout << ans[k] << " ";
  }
  cout << nl;

  return 0;
}
