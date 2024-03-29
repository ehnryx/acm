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

constexpr int to_int(char c) { return c - 'a'; }

static constexpr int A = 26;
struct node {
  int fail;
  int pattern;
  int child[A];
  node(): fail(0), pattern(-1) {
    memset(child, -1, sizeof(child));
  }
};
node nodes[N];

struct aho_corasick {
  static constexpr int root = 0;
  int nns;
  int size() const { return nns; }
  const auto& operator[](int i) const { return nodes[i]; }

  aho_corasick(): nns(1) {}

  void add(int i, const string& s) {
    int u = root;
    for(char c : s) {
      if(nodes[u].child[to_int(c)] == -1) {
        nodes[u].child[to_int(c)] = nns++;
      }
      u = nodes[u].child[to_int(c)];
    }
    nodes[u].pattern = i;
  }

  void build() {
    queue<int> bfs;
    bfs.emplace(0);
    while(not empty(bfs)) {
      auto u = bfs.front();
      bfs.pop();
      for(int i=0; i<A; i++) {
        if(int v = nodes[u].child[i]; v != -1) {
          nodes[v].fail = (u == root ? root : follow(nodes[u].fail, i));
          bfs.emplace(v);
        }
      }
    }
  }

  int follow(int u, int c) {
    int from = u;
    while(u != root and nodes[u].child[c] == -1) {
      u = nodes[u].fail;
    }
    if(nodes[u].child[c] != -1) {
      u = nodes[u].child[c];
    }
    return nodes[from].child[c] = u;
  }

  vector<vector<int>> build_fail_tree() const {
    vector<vector<int>> fail_tree(size());
    for(int i=1; i<size(); i++) {
      fail_tree[nodes[i].fail].push_back(i);
    }
    return fail_tree;
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  aho_corasick ac;
  for(int i=0; i<m; i++) {
    string s;
    cin >> s;
    ac.add(i, s);
  }
  ac.build();

  segtree st;

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
      for(int u=0, i=0; i<size(s); i++) {
        u = ac.follow(u, to_int(s[i]));
        res += st.query(start[u]);
      }
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


