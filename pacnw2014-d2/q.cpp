#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';


int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }
    int one = min_element(a.begin(), a.end()) - a.begin();

    vector dp(n, vector(n, vector<int>(n, -1)));
    function<bool(int,int,int)> win = [&](int l, int r, int e) {
      if(dp[l][r][e] != -1) return dp[l][r][e];
      if(l == r) return dp[l][r][e] = true;
      bool ok = false;
      if(e > 0) ok |= !win(l, r, e-1);
      for(int i=l; i<=r && !ok; i++) {
        if(i > l && a[i] < a[i-1]) continue;
        if(i < r && a[i] < a[i+1]) continue;
        if(i == l) {
          ok |= !win(i+1, r, e);
        } else if(i == r) {
          ok |= !win(l, i-1, e);
        } else if(one < i) {
          ok |= !win(l, i-1, e + r-i);
        } else {
          ok |= !win(i+1, r, e + i-l);
        }
      }
      return dp[l][r][e] = ok;
    };

    if(win(0, n-1, 0)) {
      cout << "Alice" << nl;
    } else {
      cout << "Bob" << nl;
    }
  }

  return 0;
}
