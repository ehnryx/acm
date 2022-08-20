#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "ds/union_find.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    int n, m;
    cin >> n >> m;
    function<int(int, int)> get = [m](int i, int j) {
      return i*m + j;
    };
    auto g = cin.read<int>(n, m);
    union_find<> dsu(n * m);
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        vector<pair<int, int>> nbs;
        for(auto [di, dj] : {
            pair(0, 1), pair(0, -1), pair(1, 0), pair(-1, 0) }) {
          int ni = i + di;
          int nj = j + dj;
          if(ni < 0 || n <= ni) continue;
          if(nj < 0 || m <= nj) continue;
          if(g[i][j] > g[ni][nj]) {
            nbs.emplace_back(g[ni][nj], get(ni, nj));
          }
        }
        if(!empty(nbs)) {
          dsu.link(get(i, j), min_element(begin(nbs), end(nbs))->second);
        }
      }
    }

    cout << "Case #" << tt << ":" << nl;
    map<int, char> out;
    char at = 'a';
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        int k = dsu.find(get(i, j));
        if(!out.count(k)) {
          out[k] = at++;
        }
        cout << out[k] << " ";
      }
      cout << nl;
    }
  }

  return 0;
}
