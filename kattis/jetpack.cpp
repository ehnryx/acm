#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/graph_list.h"
%:include "graph/graph_vector.h"
%:include "graph/breadth_first.h"

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

  int n = 10;
  int m;
  cin >> m;
  auto grid = cin.read<char>(n, m);
  function<int(int, int)> get = [m](int i, int j) {
    return i*m + j;
  };

  GraphList<void> g(n*m + 1);
  const int sink = n*m;
  const int source = get(9, 0);
  for(int i=0; i<n; i++) {
    for(int j=1; j<m; j++) {
      if(grid[i][j] == 'X') continue;
      g.add_arc(get(max(0, i-1), j-1), get(i, j));
      g.add_arc(get(min(9, i+1), j-1), get(i, j));
      if(j+1 == m) g.add_arc(get(i, j), sink);
    }
  }

  auto path = breadth_first(g).run(source).get_path(sink);
  assert(size(path) == m + 1);
  vector<pair<int, int>> ans;
  for(int i=1; i+1<path.size(); i++) {
    if(path[i]/m <= path[i-1]/m && path[i] < source) {
      if(!ans.empty() && ans.back().first + 1 == i-1) {
        ans.back().second++;
      } else {
        ans.emplace_back(i-1, 1);
      }
    }
  }
  cout << size(ans) << nl;
  for(auto [a, b] : ans) {
    cout << a << " " << b << nl;
  }

  return 0;
}
