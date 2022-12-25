#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<unordered_set<int>> adj(n+1);

  ll non = (ll)n * (n-1) / 2 - m;
  if(non < m) {
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        if(j != i) {
          adj[i].insert(j);
        }
      }
    }
  }

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    if(non < m) {
      adj[a].erase(b);
      adj[b].erase(a);
    } else {
      adj[a].insert(b);
      adj[b].insert(a);
    }
  }

  vector<int> big, small;
  for(int i=1; i<=n; i++) {
    if(size(adj[i]) * 2 < n-1) {
      small.push_back(i);
    } else {
      big.push_back(i);
    }
  }

  static constexpr int ITERS1 = 3;
  static constexpr int ITERS2 = 2;

  vector<int> path, tail;

  // 1 is big
  if(not empty(big) and big[0] == 1) {
    vector<int> order(n-1), rem;
    iota(begin(order), end(order), 2);
    while(clock() < 0.5 * CLOCKS_PER_SEC) {
      for(int t=0; t<ITERS1; t++) {
        shuffle(begin(order), end(order), rng);
        vector<int> cur = { 1 }, todo;
        for(int v : order) {
          if(adj[cur.back()].count(v)) {
            cur.push_back(v);
          } else {
            todo.push_back(v);
          }
        }
        if(size(cur) > size(path)) {
          path = move(cur);
          rem = move(todo);
        }
      }
    }
    order = move(rem);

    if(not empty(order)) {
      for(int t=0; t<ITERS2; t++) {
        while(clock() < 2.8 * CLOCKS_PER_SEC) {
          shuffle(begin(order), end(order), rng);
          vector<int> cur = { order[0] }, todo;
          for(int i=1; i<size(order); i++) {
            if(not adj[cur.back()].count(order[i])) {
              cur.push_back(order[i]);
            } else {
              todo.push_back(order[i]);
            }
          }
          if(size(cur) > size(tail)) {
            tail = move(cur);
            rem = move(todo);
          }
        }
      }
    }
  }

  // 1 is small
  else {
    vector<int> order(n-1), rem;
    iota(begin(order), end(order), 2);
    while(clock() < 0.5 * CLOCKS_PER_SEC) {
      for(int t=0; t<ITERS1; t++) {
        shuffle(begin(order), end(order), rng);
        vector<int> cur = { 1 }, todo;
        for(int v : order) {
          if(not adj[cur.back()].count(v)) {
            cur.push_back(v);
          } else {
            todo.push_back(v);
          }
        }
        if(size(cur) > size(path)) {
          path = move(cur);
          rem = move(todo);
        }
      }
    }
    order = move(rem);

    if(not empty(order)) {
      while(clock() < 2.8 * CLOCKS_PER_SEC) {
        for(int t=0; t<ITERS2; t++) {
          shuffle(begin(order), end(order), rng);
          vector<int> cur = { order[0] }, todo;
          for(int i=1; i<size(order); i++) {
            if(adj[cur.back()].count(order[i])) {
              cur.push_back(order[i]);
            } else {
              todo.push_back(order[i]);
            }
          }
          if(size(cur) > size(tail)) {
            tail = move(cur);
            rem = move(todo);
          }
        }
      }
    }
  }

  path.insert(end(path), rbegin(tail), rend(tail));
  assert(size(path) == n);
  for(int v : path) {
    cout << v << " ";
  }
  cout << nl;
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
