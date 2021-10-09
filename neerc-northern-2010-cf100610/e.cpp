#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
const char nl = '\n';

#define FILE "explicit"

int main() {
  if (fopen(FILE ".in", "r")) {
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
  }
  const int n = 10;
  int nums[n];
  for (int i = 0 ; i < n; ++i)
    cin >> nums[i];
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      ans ^= (nums[i] | nums[j]);
      for (int k = 0; k < j; k++) {
        ans ^= (nums[i] | nums[j] | nums[k]);
      }
    }
  }
  cout << ans << nl;

  return 0;
}

