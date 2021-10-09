#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 1e9+7;
const ll INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

#define End return 0; }
#define of ios::sync_with_stdio(0); cin.tie(0);
#define story int main() {
#define The

The story of lame:

  ll i, n, ans;
  int T;
  cin >> T;
  while (T--) {
    cin >> i >> n;
    ans = n;
    while (n != 1) {
      if (n%2 == 0) n/=2;
      else n = 3*n+1;
      ans = max(ans, n);
    }
    cout << i << " " << ans << endl;
  }

The End
