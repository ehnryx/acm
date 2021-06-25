#include <bits/stdc++.h>
using namespace std;

#include "../../lca/tree/rooted_tree.h"
#include "../../lca/number/capped_int.h"

const char nl = '\n';
using ll = long long;
using ld = long double;
using Int = capped_int<(ll)1e18 + 7>;

void solve(const rooted_tree& adj, int u, vector<vector<Int>>& subcnt) {
  vector<Int>& cnt = subcnt[u];
  cnt.resize(2, 1);
  int cur_size = 1;
  for (int v : adj[u]) {
    solve(adj, v, subcnt);
    cur_size += adj.subtree[v];
    vector<Int> new_cnt = cnt;
    new_cnt.resize(cur_size + 1);
    for (int i = 1; i <= adj.subtree[v]; i++) {
      for (int j = 1; j < (int)cnt.size(); j++) {
        new_cnt[i + j] += cnt[j] * subcnt[v][i];
      }
    }
    cnt = move(new_cnt);
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n; ll k;
  cin >> n >> k;
  vector<vector<int>> adj(n + 1);
  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  rooted_tree tree(move(adj), 1);

  vector<vector<Int>> subcnt(n + 1);
  solve(tree, 1, subcnt);

  vector<Int> cnt(n + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < (int)subcnt[i].size(); j++) {
      cnt[j] += subcnt[i][j];
    }
  }
  partial_sum(begin(cnt), end(cnt), begin(cnt));

  auto it = lower_bound(begin(cnt), end(cnt), k);
  if (it == end(cnt)) cout << -1 << nl;
  else cout << it - begin(cnt) << nl;

  return 0;
}
