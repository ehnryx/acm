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
random_device _rd; mt19937 rng(_rd());



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
    int n, m;
    cin >> n >> m;
    vector<multiset<pair<int,int>>> adj(n + 1);
    for(int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      adj[a].insert(pair(b, c));
      adj[b].insert(pair(a, c));
    }
    vector<int> rem;
    for(int i=1; i<=n; i++) {
      if(size(adj[i]) == 2) {
        rem.push_back(i);
      }
    }
    for(int u : rem) {
      auto [a, da] = *adj[u].begin();
      auto [b, db] = *adj[u].rbegin();
      adj[u].clear();
      adj[a].erase(adj[a].find(pair(u, da)));
      adj[b].erase(adj[b].find(pair(u, db)));
      if (a == b) {
        adj[a].insert(pair(a, da + db));
      } else {
        adj[a].insert(pair(b, da + db));
        adj[b].insert(pair(a, da + db));
      }
    }
    vector<tuple<int,int,int>> out;
    for(int i=1; i<=n; i++) {
      for(auto [j, c] : adj[i]) {
        if(j < i) continue;
        out.emplace_back(i, j, c);
      }
    }
    cout << size(out) << nl;
    for(auto [a, b, c] : out) {
      cout << a << " " << b << " " << c << nl;
    }
    cout << nl;
  }

  return 0;
}
