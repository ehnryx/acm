#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 5e4 + 7;
char win[N];
bool isp[N + 1];
bool solve(int n) {
  if(win[n] != -1) return win[n];
  bool res = false;
  for(int i=1; i<=n; i++) {
    if(isp[i+1] && !solve(n - i)) {
      res = true;
      break;
    }
  }
  win[n] = res;
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  memset(win, -1, sizeof win);
  for(int i=2; i<=N; i++) {
    bool ok = true;
    for(int j=2; j*j<=i; j++) {
      ok &= (i % j != 0);
    }
    isp[i] = ok;
  }

  vector<int> bad;
  for(int i=1; i<N; i++) {
    if(!solve(i)) {
      bad.push_back(i);
    }
  }

  vector<int> diff;
  adjacent_difference(begin(bad), end(bad), back_inserter(diff));

  //for(int it : bad) { cout << it << nl; }
  for(int it : diff) { cout << it << nl; }

  return 0;
}
