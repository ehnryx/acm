#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
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

  static const int eps = 10 + '0';

  string reg;
  cin >> reg;
  reg = "(" + reg + ")";

  string s;
  cin >> s;

  int uid = 0;
  int cur = 0;
  int last = 0;

  const int max_nodes = 2 * reg.size() + 1;
  stack<pair<int, int>> range;
  pair<int, int> group;

  vector adj(max_nodes, vector<int>(10, -1));
  function<void(int, int, int)> add_edge = [&](int a, int b, int c) {
    if(c == eps) {
      adj[a].push_back(b);
    } else {
      adj[a][c - '0'] = b;
    }
  };

  bool in_bracket = false;
  for (char c : reg) {
    if(c == '(') {
      cur = ++uid;
      add_edge(last, cur, eps);
      // range last -> cur
      last = cur;
      cur = ++uid;
      range.emplace(last, cur);
    } else if(c == '[') {
      cur = ++uid;
      add_edge(last, cur, eps);
      // parallel last -> cur
      last = cur;
      cur = ++uid;
      in_bracket = true;
    } else if(c == '+') {
      add_edge(group.second, group.first, eps);
    } else if(c == '|') {
      add_edge(last, range.top().second, eps);
      last = range.top().first;
    } else if(c == ')') {
      add_edge(last, range.top().second, eps);
      last = range.top().second;
      group = range.top();
      range.pop();
    } else if(c == ']') {
      group = pair(last, cur);
      last = cur;
      in_bracket = false;
    } else if(isdigit(c)) {
      if(in_bracket) {
        add_edge(last, cur, c);
      } else {
        cur = ++uid;
        add_edge(last, cur, eps);
        last = cur;
        cur = ++uid;
        add_edge(last, cur, c);
        group = pair(last, cur);
        last = cur;
      }
    } else {
      assert(false);
    }
  }

#ifdef DEBUG
  for(int i=0; i<=uid; i++) {
    cerr << setw(2) << i << " -> ";
    for(int j=0; j<adj[i].size(); j++) {
      if(adj[i][j] != -1) {
        cerr << "(" << j << ", " << adj[i][j] << ")  ";
      }
    }
    cerr << nl;
  }
#endif

  int n = uid + 1;
  // go from 1 to 2
  static const int source = 1;
  static const int sink = 2;
  int m = s.size();

  vector dist(m + 1, vector<int>(n, -1));
  deque<tuple<int, int, int>> bfs;
  bfs.emplace_back(0, source, 0);

  while(!empty(bfs)) {
    auto [i, u, d] = bfs.front();
    bfs.pop_front();

    if(dist[i][u] != -1) continue;
    dist[i][u] = d;

    // follow
    if(int to = adj[u][s[i] - '0']; i < m && to != -1) {
      if(dist[i+1][to] == -1) {
        bfs.emplace_front(i + 1, to, d);
      }
    }

    // delete
    if(i < m) {
      if(dist[i+1][u] == -1) {
        bfs.emplace_back(i + 1, u, d + 1);
      }
    }

    // insert & change
    for(int c=0; c<10; c++) {
      if(adj[u][c] == -1) continue;
      int to = adj[u][c];
      // insert
      if(dist[i][to] == -1) {
        bfs.emplace_back(i, to, d + 1);
      }
      // change
      if(i < m && dist[i+1][to] == -1) {
        bfs.emplace_back(i+1, to, d + 1);
      }
    }

    // follow eps
    for(int c=10; c<adj[u].size(); c++) {
      int to = adj[u][c];
      if(dist[i][to] == -1) {
        bfs.emplace_front(i, to, d);
      }
    }
  }

  assert(dist[m][sink] != -1);
  cout << dist[m][sink] << nl;

  return 0;
}
