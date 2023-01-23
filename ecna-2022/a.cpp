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
  int n, m;
  cin >> n >> m;
  static constexpr int N = 100;
  vector<int> parent(N, -1);
  unordered_map<string, int> remap;
  for(int i=0, rid=0; i<n; i++) {
    string s;
    cin >> s;
    if(not remap.count(s)) remap[s] = rid++;
    int at = remap[s];
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      cin >> s;
      if(not remap.count(s)) remap[s] = rid++;
      int cur = remap[s];
      parent[cur] = at;
    }
  }
  assert(size(remap) <= N);
  parent.resize(size(remap));

  vector<int> depth(size(parent));
  for(int i=0; i<size(depth); i++) {
    for(int j=i; j!=-1; j=parent[j]) {
      depth[i]++;
    }
  }

  auto lca = [&](int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    while(depth[a] > depth[b]) {
      a = parent[a];
    }
    while(a != b) {
      a = parent[a];
      b = parent[b];
    }
    assert(a != -1);
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

  auto get_cousin = [](int d) -> string {
    assert(d > 0);
    if(d-1 == 11 or d-1 == 12 or d-1 == 13) {
      return to_string(d-1) + "th";
    }
    switch((d-1) % 10) {
      case 1: return to_string(d-1) + "st";
      case 2: return to_string(d-1) + "nd";
      case 3: return to_string(d-1) + "rd";
      default: return to_string(d-1) + "th";
    };
  };

  auto indirect = [&](int a, int b, int c) -> string {
    assert(depth[a] >= depth[c]);
    assert(depth[b] >= depth[c]);
    int da = depth[a] - depth[c];
    int db = depth[b] - depth[c];
    assert(min(da, db) > 0);
    if(da == db) {
      if(da == 1) {
        return "siblings";
      } else {
        return get_cousin(da) + " cousins";
      }
    } else {
      int diff = abs(da - db);
      return get_cousin(min(da, db)) + " cousins, " + to_string(diff) +
        " time" + (diff == 1 ? "" : "s") + " removed";
    }
  };

  for(int i=0; i<m; i++) {
    string a, b;
    cin >> a >> b;
    assert(remap.count(a) and remap.count(b));
    int ai = remap[a];
    int bi = remap[b];
    int ci = lca(ai, bi);
    if(ai == ci) {
      cout << b << " is the " << direct(ai, bi) << " of " << a << nl;
    } else if(bi == ci) {
      cout << a << " is the " << direct(ai, bi) << " of " << b << nl;
    } else {
      cout << a << " and " << b << " are " << indirect(ai, bi, ci) << nl;
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
