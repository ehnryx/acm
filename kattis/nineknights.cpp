#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  const int n = 5;
  vector g(n, vector<char>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
    }
  }
  int cnt = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(g[i][j] != 'k') continue;
      cnt++;
      for(auto [di, dj] : {
          pair(1, 2), pair(2, 1),
          pair(-1, 2), pair(2, -1),
          pair(1, -2), pair(-2, 1),
          pair(-1, -2), pair(-2, -1),
          }) {
        int ni = i + di;
        int nj = j + dj;
        if(ni<0 or n<=ni or nj<0 or n<=nj) continue;
        if(g[ni][nj] == 'k') {
          return void(cout << "invalid" << nl);
        }
      }
    }
  }
  cout << (cnt == 9 ? "" : "in") << "valid" << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
