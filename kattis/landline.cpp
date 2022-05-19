#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int solve_bad(int n, int m) {
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
  }

  if(n*(n-1)/2 != m) {
    cout << "impossible" << nl;
    return 0;
  }

  int ans = 0;
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ans += c;
  }
  cout << ans << nl;

  return 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m, k;
  cin >> n >> m >> k;

  if(k == n) {
    return solve_bad(n, m);
  }

  vector<bool> bad(n+1);
  for(int i=0; i<k; i++) {
    int v;
    cin >> v;
    bad[v] = true;
  }

  vector<tuple<int, int, int>> edges;
  vector<unsigned> con(n+1, -1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if(!bad[a] && !bad[b]) {
      edges.emplace_back(c, a, b);
    } else if(bad[a] && !bad[b]) {
      con[a] = min(con[a], (unsigned)c);
    } else if(bad[b] && !bad[a]) {
      con[b] = min(con[b], (unsigned)c);
    }
  }
  sort(begin(edges), end(edges));

  int ans = 0;
  int groups = n;
  for(int i=1; i<=n; i++) {
    if(bad[i]) {
      if(con[i] == -1) {
        cout << "impossible" << nl;
        return 0;
      }
      ans += con[i];
      groups--;
    }
  }

  vector<int> dsu(n+1, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<bool(int, int)> link = [&](int i, int j) {
    if(find(i) == find(j)) return false;
    dsu[find(i)] = find(j);
    return true;
  };

  for(auto [c, a, b] : edges) {
    if(link(a, b)) {
      ans += c;
      groups--;
    }
  }

  if(groups > 1) {
    cout << "impossible" << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
