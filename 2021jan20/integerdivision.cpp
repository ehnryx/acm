#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, d;
  cin >> n >> d;
  map<int,int> count;
  for(int i=0; i<n; i++) {
    int ai;
    cin >> ai;
    count[ai / d] += 1;
  }

  long long ans = 0;
  for(auto [_, c] : count) {
    ans += (long long) c * (c-1) / 2;
  }
  cout << ans << nl;

  return 0;
}
