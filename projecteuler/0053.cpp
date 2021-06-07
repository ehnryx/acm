#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  //ll n = 100;
  //if (argc > 1) n = atoll(argv[1]);

  int ans = 0;
  for(int n=1; n<=100; n++) {
    for(int r=0; r<=n; r++) {
      Int val = 1;
      for(int i=1; i<=n; i++) {
        val *= i;
      }
      for(int i=1; i<=r; i++) {
        val /= i;
      }
      for(int i=1; i<=n-r; i++) {
        val /= i;
      }
      if(val > 1'000'000) {
        ans++;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
