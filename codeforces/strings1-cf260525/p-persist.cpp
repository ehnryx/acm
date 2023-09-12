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

const int L = 17;
const int N = 1 << L;
struct node {
  int val;
  int l;
  int r;
};
vector<node> st = { node{0, -1, -1} };
int st_update(int l, int r, int v, int o, int s=0, int e=N) {
  if(r<=s or e<=l) return o == -1 ? -1 : o;
  int i = size(st);
  st.push_back({
    o == -1 ? 0 : st[o].val,
    o == -1 ? -1 : st[o].l,
    o == -1 ? -1 : st[o].r,
  });
  if(l<=s and e<=r) {
    st[i].val += v;
  } else {
    int m = (s+e) / 2;
    st[i].l = st_update(l, r, v, o == -1 ? -1 : st[o].l, s, m);
    st[i].r = st_update(l, r, v, o == -1 ? -1 : st[o].r, m, e);
  }
  return i;
}
ll st_query(int x, int i, int s=0, int e=N) {
  if(i == -1) return 0;
  int m = (s+e) / 2;
  if(x < m) return st[i].val + st_query(x, st[i].l, s, m);
  else return st[i].val + st_query(x, st[i].r, m, e);
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
  st.reserve(1 + 4*N*L);
  vector<int> root(n+1);
  for(int i=0; i<n; i++) {
    int u = ac.leaf[remap[i]];
    root[i+1] = st_update(start[u], start[u] + sz[u], 1, root[i]);
  }
  for(auto [l, r, k, i] : small) {
    for(int u = ac.leaf[remap[k]]; u; u = ac[u].parent) {
      ans[i] += st_query(start[u], root[r]) - st_query(start[u], root[l]);
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
  assert(st.capacity() == 1 + 4*N*L);
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
