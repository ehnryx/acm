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
    static const int M = 1000 + 1;
    vector<int> cnt(M);
    for(int i=0; i<n; i++) {
      int v;
      cin >> v;
      cnt[v]++;
    }
    int ans = max_element(cnt.begin(), cnt.end()) - cnt.begin();
    cout << ans << nl;
  }

  return 0;
}
