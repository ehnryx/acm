#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/suffix_tree.h"
%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string A, B, C;
  cin >> A >> B >> C;
  string s = A + "0" + B + "1" + C + "2";
  suffix_tree st(s);
  int sa = size(A);
  int sb = size(A) + 1 + size(B);
  int sc = size(A) + 1 + size(B) + 1 + size(C);

  vector<Int> ans(min({size(A), size(B), size(C)}) + 1);
  vector cnt(st.size(), vector<int>(3));
  auto solve = [&](auto&& self, int u) -> void {
    if(st[u].left <= sa and sa < st[u].right) {
      cnt[u][0]++;
      return;
    } else if(st[u].left <= sb and sb < st[u].right) {
      cnt[u][1]++;
      return;
    } else if(st[u].left <= sc and sc < st[u].right) {
      cnt[u][2]++;
      return;
    } else {
      for(auto [_, v] : st[u]) {
        self(self, v);
        for(int i=0; i<3; i++) {
          cnt[u][i] += cnt[v][i];
        }
      }
    }
    Int cur = Int(cnt[u][0]) * Int(cnt[u][1]) * Int(cnt[u][2]);
    ans[st.depth(u) + st.length(u)] += -cur;
    ans[st.depth(u)] += cur;
  };
  solve(solve, st.root());

  Int out = ans[0];
  for(auto it : ans | views::drop(1)) {
    cout << out << " ";
    out += it;
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
