#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 1e14;
  if(argc > 1) n = atoll(argv[1]);
  const vector<ll> sep = {
    1'000'000'000,
    10'000'000'000,
    100'000'000'000,
    500'000'000'000,
    1'000'000'000'000,
    2'000'000'000'000,
    4'000'000'000'000,
    6'000'000'000'000,
    8'000'000'000'000,
    9'000'000'000'000,
    10'000'000'000'000,
    15'000'000'000'000,
    20'000'000'000'000,
    25'000'000'000'000,
    30'000'000'000'000,
    35'000'000'000'000,
    40'000'000'000'000,
    45'000'000'000'000,
    50'000'000'000'000,
    55'000'000'000'000,
    60'000'000'000'000,
    65'000'000'000'000,
    70'000'000'000'000,
    75'000'000'000'000,
    80'000'000'000'000,
    85'000'000'000'000,
    90'000'000'000'000,
    100'000'000'000'000,
  };

  int s = sqrt(n);
  cerr << "sqrt = " << s << nl;
  vector<vector<ll>> good(size(sep));
  const int mask = (1 << 24) - 1;
  for(int k=2, iters=0; k<=s; k++) {
    for(int c=k; c<=s; c+=k, iters++) {
      int a = c + k;
      int x = a + c - c / k;
      int b = x - a;
      //int d = x - c - 1;
      if((ll)a*b <= n) {
        int j = lower_bound(begin(sep), end(sep), (ll)a*b) - begin(sep);
        good[j].push_back((ll)a*b);
      }
      if ((iters & mask) == 0) {
        cerr << "AT " << iters << " iters : ";
        int ans = 0;
        for(int i=0; i<size(sep); i++) {
          if(i > 0) cerr << " + ";
          ans += size(good[i]);
          cerr << size(good[i]);
        }
        cerr << " = " << ans << nl;
        cerr << "\tk = " << k << nl;
      }
    }
  }

  int ans = 0;
  for(int i=0; i<size(sep); i++) {
    cerr << "sorting " << i << " / " << size(sep) << nl;
    sort(begin(good[i]), end(good[i]));
    ans += unique(begin(good[i]), end(good[i])) - begin(good[i]);
  }
  cout << ans << nl;

  return 0;
}
