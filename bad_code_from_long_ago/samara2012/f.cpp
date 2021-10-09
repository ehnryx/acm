#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  long long ans = 0;
  set<int> seen;
  int left, right, curr;
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> curr;
    auto it = seen.lower_bound(curr);
    if (it == seen.end()) 
      right = n+1;
    else 
      right = *it;
    if (it == seen.begin()) 
      left = 0;
    else
      left = *(--it);
    ans += right-left-2;
    seen.insert(curr);
  }
  cout << ans << '\n';

  return 0;
}
