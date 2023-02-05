#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/aho_corasick.h"
%:include "string/to_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct row_view {
  const vector<vector<char>>& g;
  int row;
  row_view(const vector<vector<char>>& _g, int r): g(_g), row(r) {}
  int size() const { return g[row].size(); }
  char operator[](int i) const { return g[row][i]; }
};

struct col_view {
  const vector<vector<char>>& g;
  int col;
  col_view(const vector<vector<char>>& _g, int c): g(_g), col(c) {}
  int size() const { return g.size(); }
  char operator[](int i) const { return g[g.size() - 1 - i][col]; }
};

struct corner_view {
  const vector<vector<char>>& g;
  int row, col;
  corner_view(const vector<vector<char>>& _g, int r, int c): g(_g), row(r), col(c) {}
  int size() const { return col + g.size() - row; }
  char operator[](int i) const { return i < col ? g[row][i] : g[row + i - col][col]; }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, p;
  cin >> n >> m >> p;
  vector g(n, vector<char>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }
  aho_corasick<char, to_int::upper> ac, rev;
  unordered_map<string, int> dups;
  vector<int> remap(p);
  for(int i=0, rid=0; i<p; i++) {
    string s;
    cin >> s;
    if(not dups.count(s)) {
      dups[s] = rid++;
      ac.add(s);
      rev.add(string(rbegin(s), rend(s)));
    }
    remap[i] = dups[s];
  }
  ac.build();
  rev.build();

  vector<int> cnt(ac.size()), rcnt(rev.size());
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      ac.find_ends(corner_view(g, i, j), [&](int u, int) { cnt[u]++; });
    }
  }
  for(int i=0; i<n; i++) {
    ac.find_ends(row_view(g, i), [&](int u, int idx) {
      cnt[u]++;
      cnt[u] -= m - idx;
    });
  }
  for(int j=0; j<m; j++) {
    rev.find_ends(col_view(g, j), [&](int u, int idx) {
      rcnt[u]++;
      rcnt[u] -= n - idx;
    });
  }

  vector<int> ans(p);

  auto fail = ac.build_fail_tree();
  auto solve = [&](auto&& self, int u) -> void {
    for(int v : fail[u]) {
      self(self, v);
      cnt[u] += cnt[v];
    }
    if(ac[u].pattern != -1) {
      ans[ac[u].pattern] = cnt[u];
    }
  };
  solve(solve, ac.root);

  auto rfail = rev.build_fail_tree();
  auto rsolve = [&](auto&& self, int u) -> void {
    for(int v : rfail[u]) {
      self(self, v);
      rcnt[u] += rcnt[v];
    }
    if(rev[u].pattern != -1) {
      ans[rev[u].pattern] += rcnt[u];
    }
  };
  rsolve(rsolve, rev.root);

  for(int i=0; i<p; i++) {
    cout << ans[remap[i]] << nl;
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
