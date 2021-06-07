#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 3e5 + 1;
vector<int> adj[N];

ll solve(int u, int p) {
  ll res = 1;
  vector<ll> children;
  for(int v : adj[u]) {
    if(v == p) continue;
    children.push_back(solve(v, u));
  }
  sort(begin(children), end(children), greater<>());
  for(int i=0; i<size(children); i++) {
    res += (i+1) * children[i];
  }
  return res;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int n, x;
    cin >> n >> x;
    for(int i=1; i<=n; i++) {
      adj[i].clear();
    }
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    ll coeff = solve(1, 0);
    cout << coeff % MOD * x % MOD << nl;
  }

  return 0;
}
