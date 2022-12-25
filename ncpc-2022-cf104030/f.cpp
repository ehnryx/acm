#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_array_lcp.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector g(n, vector<string>(n));
  vector start(n, vector<int>(n));
  string cat;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
      if(j == i) continue;
      start[i][j] = size(cat);
      cat += g[i][j];
    }
  }
  suffix_array_lcp sa(cat);
  string tac(rbegin(cat), rend(cat));
  suffix_array_lcp rev(tac);
  vector revst(n, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(j == i) continue;
      revst[i][j] = (int)size(cat) - (start[i][j] + size(g[i][j]));
      if(size(g[i][j]) != size(g[j][i])) {
        return void(cout << "NONE" << nl);
      }
    }
  }

  vector<int> ublen(n);
  vector<vector<int>> possible(n);
  for(int i=0; i<n; i++) {
    const int o = (i+1 < n ? i+1 : 0);
    int prefix = (int)size(g[i][o]) - 1;
    int suffix = (int)size(g[o][i]) - 1;
    for(int j=0; j<n; j++) {
      if(j == i or j == o) continue;
      prefix = min({ prefix, sa.lcp(start[i][j], start[i][o]), (int)size(g[i][j]) - 1 });
      suffix = min({ suffix, rev.lcp(revst[j][i], revst[o][i]), (int)size(g[j][i]) - 1 });
    }
    ublen[i] = min(prefix, suffix);
    if(ublen[i] < 0) return; // WTF??

    int pi = start[i][o];
    int si = start[o][i] + size(g[o][i]);
    for(int len=1; len<=ublen[i]; len++) {
      if(sa.lcp(pi, si - len) >= len) {
        possible[i].push_back(len);
      }
    }
    if(empty(possible[i])) {
      return void(cout << "NONE" << nl);
    }
  }

  int root = distance(begin(possible),
      min_element(begin(possible), end(possible),
        [](const auto& a, const auto& b) { return size(a) < size(b); }));

  vector<int> ans;
  int acnt = 0;
  for(int rlen : possible[root]) {
    bool ok = true;
    vector<int> length(n);
    length[root] = rlen;
    for(int i=0; i<n and ok; i++) {
      if(i == root) continue;
      length[i] = (int)size(g[i][root]) - length[root];
      auto it = lower_bound(begin(possible[i]), end(possible[i]), length[i]);
      ok &= (it != end(possible[i]) and *it == length[i]);
    }
    for(int i=0; i<n and ok; i++) {
      for(int j=0; j<n and ok; j++) {
        if(j == i) continue;
        ok &= (length[i] + length[j] == size(g[i][j]));
      }
    }
    if(ok) {
      ans = length;
      if(++acnt > 1) {
        break;
      }
    }
  }

  if(acnt == 0) {
    cout << "NONE" << nl;
  } else if(acnt > 1) {
    cout << "MANY" << nl;
  } else {
    cout << "UNIQUE" << nl;
    for(int i=0; i<n; i++) {
      const int o = (i+1 < n ? i+1 : 0);
      cout << g[i][o].substr(0, ans[i]) << nl;
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
