#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;

const int N = 2e5 + 1;
int a[N];
vector<int> idx[N], vals[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, c, k;
  cin >> n >> c >> k;
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    idx[a[i]].push_back(i);
    vals[a[i]].push_back(i - idx[a[i]].size());
  }

  int ans = 0;
  for(int i=1; i<=n; i++) {
    int j = lower_bound(idx[a[i]].begin(), idx[a[i]].end(), i) - idx[a[i]].begin();
    auto it = upper_bound(vals[a[i]].begin() + j, vals[a[i]].end(), k + vals[a[i]][j]);
    int m = it - vals[a[i]].begin();
    ans = max(ans, m - j);
  }
  cout << ans << nl;

  return 0;
}
