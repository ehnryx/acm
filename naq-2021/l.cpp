#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll nc2(ll n) {
  return n*(n-1)/2;
}

ll nc3(ll n) {
  return n*(n-1)*(n-2)/6;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n+1);
  vector<pair<int, int>> edges;
  vector<unordered_set<int>> nbs(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
    edges.emplace_back(a, b);
    nbs[a].insert(b);
    nbs[b].insert(a);
  }

  vector<ll> scnt(n+1);
  for(int i=1; i<=n; i++) {
    if(size(adj[i]) >= 4) {
      for(int j : adj[i]) {
        scnt[j] += nc3(size(adj[i]) - 1);
      }
    }
  }

  ll ans = 0;
  for(int i=1; i<=n; i++) {
    ans += scnt[i] * (size(adj[i]) - 1);
  }

  for(auto [a, b] : edges) {
    if(size(adj[a]) > size(adj[b])) swap(a, b);
    for(int c : adj[a]) {
      if(size(adj[c]) >= 4 && nbs[b].count(c)) {
        ans -= 2 * nc2(size(adj[c]) - 2);
      }
    }
  }

  cout << ans << nl;

  return 0;
}
