#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/union_find.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  vector<pair<int,int>> edges;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    edges.emplace_back(a, b);
  }

  int q;
  cin >> q;
  using vtup = vector<tuple<int,int,int,int>>;
  vtup queries;
  for(int i=0; i<q; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    queries.emplace_back(x, y, z, i);
  }

  static const int L = 18;
  vector dsu(L, union_find(n + 1));
  vector<int> cur(L);
  vector<int> ans(q);

  function<void(int,int,int,vtup)> search = [&](int layer, int l, int r, const vtup& qs) {
    if(l == r || empty(qs)) {
      for(const auto& it : qs) {
        ans[get<3>(it)] = r;
      }
      return;
    }

    int mid = (l + r) / 2;
    auto& uf = dsu[layer];
    int& j = cur[layer];
    while(j <= mid) {
      uf.link(edges[j].first, edges[j].second);
      j++;
    }

    vector<tuple<int,int,int,int>> left, right;
    for(auto [x, y, z, i] : qs) {
      if(uf[x] == uf[y]) {
        if(z <= uf.size[uf[x]]) {
          left.emplace_back(x, y, z, i);
        } else {
          right.emplace_back(x, y, z, i);
        }
      } else {
        if(z <= uf.size[uf[x]] + uf.size[uf[y]]) {
          left.emplace_back(x, y, z, i);
        } else {
          right.emplace_back(x, y, z, i);
        }
      }
    }
    search(layer + 1, l, mid, left);
    search(layer + 1, mid+1, r, right);
  };

  search(0, 0, m-1, queries);
  for(int i=0; i<q; i++) {
    cout << ans[i] + 1 << nl;
  }

  return 0;
}
