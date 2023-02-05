#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/aho_corasick.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 17;
int st[2*N];
void st_update(int l, int r, int v) {
  for(l+=N, r+=N; l<r; l/=2, r/=2) {
    if(l&1) st[l++] += v;
    if(r&1) st[--r] += v;
  }
}
ll st_query(int x) {
  ll res = 0;
  for(x+=N; x; x/=2) {
    res += st[x];
  }
  return res;
}

struct to_int {
  int operator()(char c) const { return c - 'a'; }
  static constexpr int size = 26;
};
using AC = aho_corasick<char, to_int>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, q;
  cin >> n >> q;
  vector<string> s(n);
  unordered_map<string, int> seen;
  vector<int> remap(n);

  AC ac(n, 1e5);
  for(int i=0, rid=0; i<n; i++) {
    cin >> s[i];
    if(!seen.count(s[i])) {
      seen[s[i]] = rid++;
      ac.add(s[i]);
    }
    remap[i] = seen[s[i]];
  }
  ac.build();

  auto adj = ac.build_fail_tree();
  vector<int> start(ac.size()), sz(ac.size());
  auto build = [&, uid=0](auto&& self, int u) mutable -> int {
    start[u] = uid++;
    sz[u] = 1;
    for(int v : adj[u]) {
      sz[u] += self(self, v);
    }
    return sz[u];
  };
  build(build, 0);

  auto update = [&](int i, int v) {
    int u = ac.leaf[remap[i]];
    st_update(start[u], start[u] + sz[u], v);
  };

  auto query = [&](int u) {
    return st_query(start[u]);
  };

  static constexpr int S = 320;
  vector<vector<tuple<int, int, int>>> big(remap.size());
  vector<tuple<int, int, int, int>> small;
  for(int i=0; i<q; i++) {
    int l, r, k;
    cin >> l >> r >> k;
    l--;
    r--;
    k--;
    if(size(s[k]) < S) {
      small.emplace_back(l, r + 1, k, i);  // right-exclusive
    } else {
      big[remap[k]].emplace_back(l, r + 1, i);  // right-exclusive
    }
  }

  vector<ll> ans(q);

  // solve small
  sort(begin(small), end(small), [](auto& a, auto& b) {
      int al = get<0>(a);
      int ar = get<1>(a);
      int bl = get<0>(b);
      int br = get<1>(b);
      if(al / S != bl / S) return al < bl;
      return (al / S) % 2 == 0 ? ar < br : ar > br; });
  int x = 0;
  int y = 0;
  for(auto [l, r, k, i] : small) {
    while(x < l) update(x++, -1);
    while(x > l) update(--x, 1);
    while(y < r) update(y++, 1);
    while(y > r) update(--y, -1);
    for(int u = ac.leaf[remap[k]]; u; u = ac[u].parent) {
      ans[i] += query(u);
    }
  }

  // solve large
  for(int k=0; k<size(remap); k++) {
    if(empty(big[k])) continue;
    vector<int> cnt(ac.size()), rval(remap.size());
    for(int u = ac.leaf[k]; u; u = ac[u].parent) {
      cnt[u]++;  // is part of the string
    }
    auto run = [&](auto&& self, int u) -> int{
      for(int v : adj[u]) {
        cnt[u] += self(self, v);
      }
      if(ac[u].pattern != -1) {
        rval[ac[u].pattern] += cnt[u];
      }
      return cnt[u];
    };
    run(run, 0);
    vector<ll> val(n+1);
    for(int i=0; i<n; i++) {
      val[i+1] = val[i] + rval[remap[i]];
    }
    for(auto [l, r, i] : big[k]) {
      ans[i] = val[r] - val[l];
    }
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
