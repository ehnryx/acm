#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/union_find.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, q;
  cin >> n >> m >> q;
  set<pair<int, int>> good;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    good.emplace(min(a, b), max(a, b));
  }
  vector<tuple<int, int, int>> ev;
  for(int i=0; i<q; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    ev.emplace_back(t, a, b);
    if(t == 0) {
      good.erase(pair(min(a, b), max(a, b)));
    }
  }
  reverse(begin(ev), end(ev));

  union_find dsu(n);
  for(auto [a, b] : good) {
    dsu.link(a, b);
  }

  vector<bool> ans;
  for(auto [t, a, b] : ev) {
    if(t == 0) {
      dsu.link(a, b);
    } else {
      ans.push_back(dsu[a] == dsu[b]);
    }
  }
  reverse(begin(ans), end(ans));

  for(auto x : ans) {
    cout << (x ? "safe" : "unsafe") << nl;
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
