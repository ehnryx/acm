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
  int n, m, q;
  cin >> n >> m >> q;
  map<int, vector<pair<int, int>>> edges;
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[c].emplace_back(a, b);
  }
  vector<unordered_set<int>> todo(n+1);
  for(int i=0; i<q; i++) {
    int a, b;
    cin >> a >> b;
    todo[a].insert(i);
    todo[b].insert(i);
  }

  vector<pair<int, int>> ans(q);
  union_find<> dsu(n+1);
  for(const auto& [c, es] : edges) {
    vector<pair<int, int>> res;
    for(auto [a, b] : es) {
      a = dsu[a];
      b = dsu[b];
      if(a == b) continue;
      dsu.link(a, b);
      if(size(todo[a]) < size(todo[b])) {
        swap(a, b);
      }
      for(int i : todo[b]) {
        if(auto [it, ok] = todo[a].insert(i); not ok) {
          todo[a].erase(it);
          res.emplace_back(i, a);
        }
      }
      todo[dsu[a]] = move(todo[a]);
    }
    for(auto [i, v] : res) {
      ans[i] = pair(c, dsu.size(v));
    }
  }

  for(auto [a, b] : ans) {
    cout << a << " " << b << nl;
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
