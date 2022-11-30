#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "math/fft.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = complex<ld>;

const ld PI = acos(ld(-1));

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int np, mp;
  cin >> np >> mp;
  pt goal = 0;
  vector pattern(np, vector<int>(mp));
  for(int i=0; i<np; i++) {
    for(int j=0; j<mp; j++) {
      cin >> pattern[i][j];
      goal += !!pattern[i][j];
    }
  }
  int n, m;
  cin >> n >> m;
  vector<pt> grid(n * m);
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      int v;
      cin >> v;
      grid[i*m + j] = exp(pt(0, 2 * PI * (v-1) / 100));
    }
  }

  if(np > n or mp > m) {
    cout << 0 << nl;
    return;
  }

  vector<pt> mat(np * m);
  for(int i=0; i<np; i++) {
    for(int j=0; j<mp; j++) {
      if(pattern[i][j]) {
        mat[i*m + j] = exp(pt(0, 2 * PI * -(pattern[i][j]-1) / 100));
      }
    }
  }
  reverse(begin(mat), end(mat));

  vector<pair<int, int>> ans;

  auto res = fft::convolve(grid, mat);
  const int offset = size(mat) - 1;
  for(int i=0; i+np<=n; i++) {
    for(int j=0; j+mp<=m; j++) {
      if(abs(res[i*m + j + offset] - goal) < EPS) {
        ans.emplace_back(i, j);
      }
    }
  }

  cout << size(ans) << nl;
  for(auto [x, y] : ans) {
    cout << x + 1 << " " << y + 1 << nl;
  }
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
