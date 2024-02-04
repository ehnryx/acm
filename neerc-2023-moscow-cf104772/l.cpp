%:include "utility/nd_array.h"
%:include "graph/topological_sort.h"
%:include "graph/graph.h"
enum { LEFT, RIGHT, UP, DOWN };
#include <deque>
%:include "main.h"
SOLVE() {
  int n, m;
  cin >> n >> m;
  nd_array<int, 2> ans(n, m);
  vector<int> dir(m, RIGHT);
  graph_t<void, graph_traits::IN_DEGREE> g(n * m);
  for (int i = 1; i < n; i++) {
    int vert = UP;
    for (int j = 1; j < m; j++) {
      char t;
      cin >> t;
      int TL = ans.index(i - 1, j - 1);
      int TR = ans.index(i - 1, j - 0);
      int BL = ans.index(i - 0, j - 1);
      int BR = ans.index(i - 0, j - 0);
      if (t == '1') {
        if (dir[j] == RIGHT) {
          g.add_arc(TL, TR);
          g.add_arc(BL, BR);
        } else {
          g.add_arc(TR, TL);
          g.add_arc(BR, BL);
        }
        if (vert == DOWN) {
          g.add_arc(TL, BR);
          g.add_arc(TR, BL);
        } else {
          g.add_arc(BR, TL);
          g.add_arc(BL, TR);
        }
      } else if (t == '2') {
        if (dir[j] == RIGHT) {
          g.add_arc(TL, TR);
          g.add_arc(BR, BL);
        } else {
          g.add_arc(TR, TL);
          g.add_arc(BL, BR);
        }
        dir[j] ^= 1;
        if (vert == DOWN) {
          g.add_arc(TL, BL);
          g.add_arc(TR, BR);
        } else {
          g.add_arc(BL, TL);
          g.add_arc(BR, TR);
        }
      } else if (t == '3') {
        if (dir[j] == RIGHT) {
          g.add_arc(TL, BR);
          g.add_arc(BL, TR);
        } else {
          g.add_arc(TR, BL);
          g.add_arc(BR, TL);
        }
        if (vert == DOWN) {
          g.add_arc(TL, BL);
          g.add_arc(TR, BR);
        } else {
          g.add_arc(BL, TL);
          g.add_arc(BR, TR);
        }
      } else {
        assert(false);
      }
    }
  }

  auto order = topological_sort(g);
  assert(size(order) == n * m);

  int uid = 1;
  for (int u : order) {
    //auto [i, j] = ans.from_index(u);
    //ans(i, j) = uid++;
    ans[u] = uid++;
  }
  //for (int i = 0; i < n; i++) {
  //  for (int j = 0; j < m; j++) {
  //    cout << ans(i, j) << " ";
  //  }
  //  cout << nl;
  //}
  for (int i = 0; i < n * m; i++) {
    cout << ans[i] << ((i + 1) % m ? " " : "\n");
  }
}
