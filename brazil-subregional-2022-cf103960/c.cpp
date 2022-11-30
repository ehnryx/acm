#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/union_find.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;

  static constexpr int M = 1e3 + 1;
  vector cuth(M, vector<bool>(M));
  vector cutv(M, vector<bool>(M));

  pair<int, int> last;
  for(int i=0; i<=n; i++) {
    int a, b;
    cin >> a >> b;
    auto cur = pair(a, b);
    if(i) {
      for(int j=min(cur.first, last.first); j<max(cur.first, last.first); j++) {
        cuth[j][cur.second] = true;
      }
      for(int j=min(cur.second, last.second); j<max(cur.second, last.second); j++) {
        cutv[cur.first][j] = true;
      }
    }
    last = cur;
  }

  auto get = [](int i, int j) {
    return i*M + j;
  };
  union_find dsu(M * M);

  for(int i=0; i<M; i++) {
    for(int j=0; j<M; j++) {
      if(i and not cutv[i][j]) {
        dsu.link(get(i, j), get(i-1, j));
      }
      if(j and not cuth[i][j]) {
        dsu.link(get(i, j), get(i, j-1));
      }
    }
  }

  int ans = 0;
  for(int i=0; i<M; i++) {
    for(int j=0; j<M; j++) {
      if(dsu[get(i, j)] != dsu[0]) {
        ans = max(ans, dsu.size(get(i, j)));
      }
    }
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
