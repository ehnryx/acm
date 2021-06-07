#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 28124;
  if (argc > 1) n = atoll(argv[1]);

  vector<int> divs(n);
  for(int i=1; i<n; i++) {
    for(int j=1; j<i; j++) {
      if(i % j == 0) {
        divs[i] += j;
      }
    }
  }

  ll ans = 0;
  for(int i=1; i<n; i++) {
    bool ok = true;
    for(int j=1; j<i; j++) {
      if(divs[j] > j && divs[i-j] > i-j) {
        ok = false;
      }
    }
    if(ok) {
      ans += i;
    }
  }
  cout << ans << nl;

  return 0;
}
