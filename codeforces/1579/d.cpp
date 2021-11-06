%:include <bits/stdc++.h>
using namespace std;

#include "../../../lca/data_structure/splay_tree.h"
#include "../../../lca/misc/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    splay_tree<splay_node<int, int>> a;
    for(int i=1; i<=n; i++) {
      int v;
      cin >> v;
      if(v) a.insert(v, i);
    }
    vector<pair<int, int>> ans;
    while(a.size() > 1) {
      pair<int, int> u = *a.rbegin();
      a.pop_back();
      pair<int, int> v = *a.rbegin();
      a.pop_back();
      ans.emplace_back(u.second, v.second);
      if(--v.first) a.insert(v.first, v.second);
      if(--u.first) a.insert(u.first, u.second);
    }
    cout << size(ans) << nl;
    for(auto [u, v] : ans) {
      cout << u << " " << v << nl;
    }
  }

  return 0;
}
