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

    vector<float> w(n), c(n);
    vector<int> dp(n, 1);
    for(int i=0; i<n; i++) {
      cin >> w[i] >> c[i];
      for(int j=0; j<i; j++) {
        if(w[i] > w[j] && c[i] < c[j]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    cout << *max_element(dp.begin(), dp.end()) << nl;
  }

  return 0;
}
