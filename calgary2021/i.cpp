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
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int,int>>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  vector<ll> degree(n+1);
  vector<int> value(n+1);
  vector<pair<int,int>> order;
  for(int i=1; i<=n; i++) {
    cin >> value[i];
    order.emplace_back(value[i], i);
    degree[i] = accumulate(adj[i].begin(), adj[i].end(), (ll)0,
      [](ll c, pair<int,int> v) -> ll {
        return v.second + c;
      }
    );
  }
  sort(order.begin(), order.end(), [](pair<int,int> a, pair<int,int> b) {
    return a.first > b.first || (a.first == b.first && a.second < b.second);
  });

  ll ans = 0;
  vector<bool> done(n+1);
  vector<ll> sol(n+1);
  for(auto [_, u] : order) {
    done[u] = true;
    sol[u] = degree[u];
    ans += degree[u] * value[u];
    for(auto [v, c] : adj[u]) {
      if(done[v]) continue;
      degree[v] -= 2 * c;
    }
  }
  cout << ans << nl;
  for(int i=1; i<=n; i++) {
    cout << sol[i] << " ";
  }
  cout << nl;

  return 0;
}
