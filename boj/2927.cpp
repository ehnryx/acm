#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/splay_tree_nodes.h"
%:include "tree/link_cut_tree.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct datav {
  int cnt = 0;
  int sum = 0;
};

struct node final : link_cut_node<node, datav> {
  void pull() {
    value.sum = left->value.sum + value.cnt + right->value.sum;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  link_cut_tree<node> graph(n+1);
  for(int i=1; i<=n; i++) {
    cin >> graph[i].value.cnt;
    graph[i].pull();
  }

  int m;
  cin >> m;
  while(m--) {
    string t;
    cin >> t;
    if(t == "bridge") {
      int a, b;
      cin >> a >> b;
      if(graph.reroot(a); graph.find_root(b) != a) {
        graph.link(a, b);
        cout << "yes" << nl;
      } else {
        cout << "no" << nl;
      }
    } else if(t == "excursion") {
      int a, b;
      cin >> a >> b;
      if(graph.reroot(a); graph.find_root(b) != a) {
        cout << "impossible" << nl;
      } else {
        cout << graph.splay(a)->value.sum << nl;
      }
    } else {
      int a, x;
      cin >> a >> x;
      int diff = x - graph[a].value.cnt;
      auto u = graph.splay(a);
      u->value.cnt += diff;
      u->pull();
    }
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
