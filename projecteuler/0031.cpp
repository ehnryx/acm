#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  //ll n = 200;
  //if (argc > 1) n = atoll(argv[1]);

  vector<Int> dp(200 + 1);
  dp[0] = 1;
  for(Int coin : {1, 2, 5, 10, 20, 50, 100, 200}) {
    vector<Int> ndp(200 + 1);
    for(Int j=200; j>=0; j-=1) {
      for(Int add=0; j+add<=200; add+=coin) {
        ndp[(j+add).value<int>()] += dp[j.value<int>()];
      }
    }
    dp = move(ndp);
  }
  cout << dp[200] << nl;

  return 0;
}
