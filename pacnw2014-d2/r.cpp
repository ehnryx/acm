#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

const int N = 80 + 17;
long long ncr[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  for(int i=0; i<N; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int n = s.size();

    bool bad = false;
    for(int i=1; i<n; i++) {
      if(s[i] < s[i-1]) {
        bad = true;
      }
    }
    if(bad) {
      cout << -1 << nl;
      continue;
    }

    long long ans = 0;
    for(int i=0; i<n; i++) {
      int pre = (i > 0 ? s[i-1]-'0' : 0);
      for(int d=pre; d<s[i]-'0'; d++) {
        // n-i-1 by 9-d
        ans += ncr[n-i-1 + 9-d][9-d];
      }
    }
    cout << ans << nl;
  }

  return 0;
}
