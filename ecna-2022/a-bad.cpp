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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int t, p;
  cin >> t >> p;
  unordered_map<string, int> remap;
  vector<int> parent;
  vector<vector<int>> adj;
  for(int i=0, rid=1; i<t; i++) {
    string s; int d;
    cin >> s >> d;
    if(not remap.count(s)) remap[s] = rid++;
    int par = remap[s];
    adj.resize(rid);
    for(int j=0; j<d; j++) {
      cin >> s;
      if(not remap.count(s)) remap[s] = rid++;
      parent.resize(rid);
      parent[remap[s]] = par;
      adj[par].push_back(remap[s]);
    }
    adj.resize(rid);
  }
  assert(size(adj) == size(parent));

  vector<int> depth(size(adj), -1);
  auto build = [&](auto&& self, int u) -> void {
    for(int v : adj[u]) {
      depth[v] = depth[u] + 1;
      self(self, v);
    }
  };

  build(build, [&]{
    int root = 1;
    while(parent[root]) {
      root = parent[root];
    }
    assert(root);
    depth[root] = 0;
    return root;
  }());

  for(int i=0; i<size(adj); i++) {
    assert((depth[i] == -1) == (i == 0));
  }

  auto lca = [&](int a, int b) {
    while(depth[a] > depth[b]) {
      a = parent[a];
    }
    while(depth[b] > depth[a]) {
      b = parent[b];
    }
    while(a != b) {
      a = parent[a];
      b = parent[b];
    }
    return a;
  };

  auto direct = [&](int a, int b) -> string {
    int d = abs(depth[a] - depth[b]);
    assert(d > 0);
    if(d == 1) {
      return "child";
    } else {
      string res;
      for(int i=2; i<d; i++) {
        res += "great ";
      }
      return res + "grandchild";
    }
  };

  auto get_cousin = [&](int d) -> string {
    assert(d >= 0);
    switch(d % 10) {
      case 1: return to_string(d) + "st";
      case 2: return to_string(d) + "nd";
      case 3: return to_string(d) + "rd";
      default: return to_string(d) + "th";
    }
  };

  auto indirect = [&](int a, int b, int c) -> string {
    int d1 = abs(depth[a] - depth[c]);
    int d2 = abs(depth[b] - depth[c]);
    assert(min(d1, d2) > 0);
    if(d1 == d2) {
      if(d1 == 1) {
        return "siblings";
      } else {
        return get_cousin(d1 - 1) + " cousins";
      }
    } else {
      return get_cousin(min(d1, d2) - 1) + " cousins, " + to_string(abs(d1 - d2)) +
        " time" + (abs(d1 - d2) == 1 ? "" : "s") + " removed";
    }
  };

  while(p--) {
    string A, B;
    cin >> A >> B;
    int a = remap[A];
    int b = remap[B];
    int c = lca(a, b);
    assert(c);
    if(c == a) {
      cout << B << " is the " << direct(a, b) << " of " << A << nl;
    } else if(c == b) {
      cout << A << " is the " << direct(a, b) << " of " << B << nl;
    } else {
      cout << A << " and " << B << " are " << indirect(a, b, c) << nl;
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
