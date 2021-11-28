#include <bits/stdc++.h>
using namespace std;

#include "../../lca/misc/fast_input.h"
#include "../../lca/data_structure/splay_tree.h"

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

  int n, m, r;
  cin >> n >> m >> r;
  splay_tree<splay_node<void, splay_tree<splay_node<int, int>>>> g;
  for(int i=0; i<n; i++) {
    g[i].insert(0, -1);
    g[i].insert(r, -1);
  }
  pair<int, int> start;
  for(int i=0; i<m; i++) {
    int lane, len, dist;
    cin >> lane >> len >> dist;
    if(i > 0) {
      g[lane].insert(dist, -1);
      g[lane].insert(dist + len, -1);
    } else {
      assert(lane == 0);
      start = pair(dist, dist + len);
    }
  }

  splay_tree<splay_node<void, splay_tree<splay_node<int, int>>>> adj;
  splay_tree<splay_node<void, pair<int, int>>> bounds;
  int nid = 0;
  for(int i=0; i<n; i++) {
    for(auto it = g[i].begin(); it != g[i].end(); it++) {
      it->value = nid;
      int a = it->key;
      int b = (++it)->key;
      it->value = nid;
      bounds.push_back(pair(a, b));
      if(i > 0) {
        auto jt = g[i-1].upper_bound(a);
        if(g[i-1].rank(jt) % 2) {
          jt = g[i-1].splay_prev(jt);
        }
        while(jt->key < b) {
        }
      }
      nid++;
    }
  }

  return 0;
}
