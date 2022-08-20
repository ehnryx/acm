#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
//%:include "graph/dynamic_connectivity.h"
%:include "ds/union_find.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 17;
vector<pair<int, int>> edges[2*N];

void add_range(int l, int r, int a, int b, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    edges[i].emplace_back(a, b);
    return;
  }
  int m = (s+e) / 2;
  add_range(l, r, a, b, 2*i, s, m);
  add_range(l, r, a, b, 2*i+1, m+1, e);
}

pair<int, bool> solve(auto& dsu, int l, int r, int k, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return pair(-1, false);

  int linked = 0;
  for(auto [a, b] : edges[i]) {
    linked += dsu.link(a, b, true);
    linked += dsu.link(a ^ 1, b ^ 1, true);
  }

  pair<int, bool> res(-1, false);

  if(s == e) {
    if(dsu.find(0) == dsu.find(k)) {
      res = pair(s, true);
    } else if(dsu.find(0) == dsu.find(k ^ 1)) {
      res = pair(s, false);
    }
  } else {
    int m = (s+e) / 2;
    res = solve(dsu, l, r, k, 2*i, s, m);
    if (res.first == -1) {
      res = solve(dsu, l, r, k, 2*i+1, m+1, e);
    }
  }

  dsu.unlink(linked);

  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m, k, t;
  cin >> n >> m >> k >> t;
  k = (k - 1) * 2;

  //dynamic_connectivity graph(2*n);
  //vector<pair<int, int>> edges;
  for(int i=0; i<m; i++) {
    int a, b;
    string s;
    cin >> a >> b >> s;
    a = (a - 1) * 2;
    b = (b - 1) * 2;
    b += (s[0] == 'i');
    //edges.emplace_back(a, b);
    if(i-t >= 0) {
      add_range(0, i-t, a, b);
    }
    if(i+1 <= m-t) {
      add_range(i+1, m-t, a, b);
    }
  }

  union_find<true, true> dsu(2*n);
  auto [ans, crew] = solve(dsu, 0, m - t, k);
  if(ans == -1) {
    cout << ans << nl;
  } else {
    cout << ans + 1 << " " << (crew ? "crewmate" : "imposter") << nl;
  }

  return 0;
}
