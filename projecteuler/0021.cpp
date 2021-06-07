#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 10'000;
  if (argc > 1) n = atoll(argv[1]);

  int m = 7 * n;
  vector<int> divs(m);
  for(int i=1; i<m; i++) {
    for(int j=1; j<i; j++) {
      if(i % j == 0) {
        divs[i] += j;
      }
    }
  }

  ll ans = 0;
  for(int i=1; i<n; i++) {
    if(divs[i] < m && divs[divs[i]] == i && divs[i] != i) {
      ans += i;
    }
  }
  cout << ans << nl;

  return 0;
}
