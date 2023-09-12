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

constexpr int N = 1 << 20;
int bit[N];
struct segtree {
  void add(int l, int r, int v) {
    add(r, -v);
    add(l, v);
  }
  void add(int x, int v) {
    for(x+=1; x<N; x+=x&-x) {
      bit[x] += v;
    }
  }
  int query(int x) {
    int res = 0;
    for(x+=1; x; x-=x&-x) {
      res += bit[x];
    }
    return res;
  }
};

struct to_int {
  int operator()(char c) const { return c - 'a'; }
  static constexpr int size = 26;
};
using Matcher = aho_corasick<char, to_int>;
//using Matcher = aho_corasick<char>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  Matcher& ac = *(new Matcher(1e6 + 1));
  for(int i=0; i<m; i++) {
    string s;
    cin >> s;
    ac.add(s);
  }
  ac.build();

  segtree& st = *(new segtree);

  auto fail = ac.build_fail_tree();
  vector<int> start(ac.size()), sz(ac.size()), remap(m);
  auto build = [&, uid=0](auto&& self, int u) mutable -> void {
    start[u] = uid++;
    for(int v : fail[u]) {
      self(self, v);
      sz[u] += sz[v];
    }
    sz[u] += 1;
    if(ac[u].pattern != -1) {
      remap[ac[u].pattern] = u;
      st.add(start[u], start[u] + sz[u], 1);
    }
  };
  build(build, ac.root);

  vector<bool> have(m, true);
  while(n--) {
    char t;
    cin >> t;
    if(t == '+') {
      int v;
      cin >> v;
      if(not have[v-1]) {
        have[v-1] = true;
        int u = remap[v-1];
        st.add(start[u], start[u] + sz[u], 1);
      }
    } else if(t == '-') {
      int v;
      cin >> v;
      if(have[v-1]) {
        have[v-1] = false;
        int u = remap[v-1];
        st.add(start[u], start[u] + sz[u], -1);
      }
    } else {
      string s;
      cin >> s;
      int res = 0;
      ac.find_ends(s, [&](int u, int) {
          res += st.query(start[u]); return true; });
      cout << res << nl;
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
