#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "math/matrix.h"
%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<2>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  static constexpr int n = 10;
  vector g(n+2, vector(n+2, '\0'));
  auto get = [&](int i, int j) {
    return i * (n+2) + j;
  };
  static constexpr int M = (n+2) * (n+2);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      cin >> g[i][j];
    }
  }

  matrix<Int> mat;
  for(int i=0; i<=n+1; i++) {
    for(int j=0; j<=n+1; j++) {
      vector<Int> row(M+1);
      if(g[i][j]) {
        row[get(i, j)] = 1;
        row[get(i+1, j)] = 1;
        row[get(i-1, j)] = 1;
        row[get(i, j+1)] = 1;
        row[get(i, j-1)] = 1;
        row.back() = (g[i][j] == 'O');
      } else {
        row[get(i, j)] = 1;
      }
      mat.push_back(move(row));
    }
  }
  mat.solve();

  int ans = 0;
  for(auto v : mat.ans) {
    ans += v.value();
  }
  cout << ans << nl;
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
