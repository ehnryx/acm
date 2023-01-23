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
  const int n = 9;
  vector g(n, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
    }
  }

  const int mask = ((1<<9) - 1) << 1;

  auto get_valid = [&](int x, int y) {
    int bx = (x / 3) * 3;
    int by = (y / 3) * 3;

    int valid = mask;
    for(int i=0; i<n; i++) {
      if(g[x][i]) valid &= ~(1 << g[x][i]);
      if(g[i][y]) valid &= ~(1 << g[i][y]);
      if(g[bx+i/3][by+i%3]) valid &= ~(1 << g[bx+i/3][by+i%3]);
    }
    return valid;
  };

  auto solve = [&](int x, int y) {
    int valid = get_valid(x, y);
    if(__builtin_popcount(valid) == 1) {
      g[x][y] = __builtin_ctz(valid);
      return true;  // made progress
    }

    // row
    {
      int others = valid;
      for(int i=0; i<n; i++) {
        if(g[x][i] == 0 and i != y) {
          others &= ~get_valid(x, i);
        }
      }
      if(__builtin_popcount(others) == 1) {
        g[x][y] = __builtin_ctz(others);
        return true;
      }
    }

    // column
    {
      int others = valid;
      for(int i=0; i<n; i++) {
        if(g[i][y] == 0 and i != x) {
          others &= ~get_valid(i, y);
        }
      }
      if(__builtin_popcount(others) == 1) {
        g[x][y] = __builtin_ctz(others);
        return true;
      }
    }

    // grid
    {
      int bx = (x / 3) * 3;
      int by = (y / 3) * 3;
      int others = valid;
      for(int i=0; i<n; i++) {
        if(g[bx + i/3][by + i%3] == 0 and pair(bx + i/3, by + i%3) != pair(x, y)) {
          others &= ~get_valid(bx + i/3, by + i%3);
        }
      }
      if(__builtin_popcount(others) == 1) {
        g[x][y] = __builtin_ctz(others);
        return true;
      }
    }

    return false;
  };

  bool done = false;
  while(not done) {
    done = true;
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(g[i][j] == 0) {
          done &= not solve(i, j);
        }
      }
    }
  }

  bool easy = true;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      easy &= (g[i][j] != 0);
    }
  }

  cout << (easy ? "Easy" : "Not easy") << nl;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(g[i][j]) cout << g[i][j];
      else cout << '.';
      cout << " ";
    }
    cout << nl;
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
