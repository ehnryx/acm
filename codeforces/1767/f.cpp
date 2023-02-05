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

struct max_set {
  static constexpr int N = 2e5 + 1;
  static constexpr int S = sqrt(N);
  vector<int> bnum, bcnt, cnt;
  max_set(): bnum(2*N), bcnt(N/S + 1), cnt(N) {}

  void add(const int v) {
    bnum[cnt[v]]--;
    cnt[v]++;
    if(cnt[v] > bcnt[v/S]) {
      bcnt[v/S]++;
    }
    bnum[cnt[v]]++;
  }
  void sub(const int v) {
    bnum[cnt[v]]--;
    if(bcnt[v/S] == cnt[v] and bnum[cnt[v]] == 0) {
      bcnt[v/S]--;
    }
    cnt[v]--;
    bnum[cnt[v]]++;
  }

  int query() const {
    int big = 0;
    for(int i=1; i*S<N; i++) {
      if(bcnt[i] > bcnt[big]) {
        big = i;
      }
    }
    int res = big*S;
    for(int i=1; i<S and big*S + i < N; i++) {
      if(cnt[big*S + i] > cnt[res]) {
        res = big*S + i;
      }
    }
    return res;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> value(n+1);
  for(int i=1; i<=n; i++) {
    cin >> value[i];
  }
  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<vector<int>> subtree(n+1);
  auto build = [&](auto&& self, int u) -> int {
    int res = 1;
    pair<int, int> big(-1, -1);
    for(int i=0; i<size(adj[u]); i++) {
      int v = adj[u][i];
      adj[v].erase(find(begin(adj[v]), end(adj[v]), u));
      int sub = self(self, v);
      big = max(big, pair(sub, i));
      res += sub;
    }
    if(big.second != -1) {
      swap(adj[u][0], adj[u][big.second]);
      subtree[u] = move(subtree[adj[u][0]]);
      for(int i=1; i<size(adj[u]); i++) {
        int v = adj[u][i];
        subtree[u].insert(end(subtree[u]), begin(subtree[v]), end(subtree[v]));
      }
    }
    subtree[u].push_back(u);
    return res;
  };
  build(build, 1);

  vector<int> index(n+1);
  vector<int> order;
  auto build_index = [&](auto&& self, int u) -> void {
    index[u] = order.size();
    order.push_back(-u); // remove self
    if(adj[u].empty()) return;

    // remove all but first subtree
    for(int i=1; i<size(adj[u]); i++) {
      for(int v : subtree[adj[u][i]]) {
        order.push_back(-v);
      }
    }

    // do first subtree
    self(self, adj[u][0]);

    // move to next subtrees
    for(int i=1; i<size(adj[u]); i++) {
      // add subtree
      for(int v : subtree[adj[u][i]]) {
        order.push_back(v);
      }
      self(self, adj[u][i]);
    }
  };
  build_index(build_index, 1);

  int q;
  cin >> q;
  vector<tuple<int, int, int>> queries;
  for(int i=0; i<q; i++) {
    int a, b;
    cin >> a >> b;
    queries.emplace_back(a, b, i);
  }
  vector<int> ans(q);

  const int M = *max_element(begin(index), end(index)) + 1;
  const int S = sqrt(M) * 4;
  sort(begin(queries), end(queries), [&](auto a, auto b) {
      if(index[get<0>(a)]/S != index[get<0>(b)]/S) {
        return index[get<0>(a)] < index[get<0>(b)];
      } else {
        return ((index[get<0>(a)]/S) % 2 == 0) == (index[get<1>(a)] < index[get<1>(b)]);
      }
    });

  max_set ds;
  for(int i=1; i<=n; i++) {
    ds.add(value[i]);
    ds.add(value[i]);
  }

  auto update = [&](int v) {
    if(v < 0) ds.sub(value[-v]);
    else ds.add(value[v]);
  };

  int x = 0;
  int y = 0;
  for(auto [a, b, i] : queries) {
    while(x < index[a]) update(order[x++]);
    while(x > index[a]) update(-order[--x]);
    while(y < index[b]) update(order[y++]);
    while(y > index[b]) update(-order[--y]);
    ans[i] = ds.query();
  }

  for(int i=0; i<q; i++) {
    cout << ans[i] << nl;
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
