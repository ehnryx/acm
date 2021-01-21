#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  vector<int> citations(n);
  for(int i=0; i<n; i++) {
    cin >> citations[i];
  }
  sort(citations.begin(), citations.end(), greater<int>());

  int ans = 0;
  for(int i=1; i<=n; i++) {
    if(citations[i-1] >= i) {
      ans = i;
    }
  }
  cout << ans << nl;

  return 0;
}
