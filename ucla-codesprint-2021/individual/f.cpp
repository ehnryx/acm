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

  int n;
  cin >> n;
  vector<tuple<int,int,ld>> edges;
  unordered_map<string,int> remap;
  remap["Emerald"] = 0;
  int rid = 1;
  for(int i=0; i<n; i++) {
    int m;
    cin >> m;
    for(int j=0; j<m; j++) {
      int a, b; string s, t;
      cin >> a >> s >> b >> t;
      if(!remap.count(s)) remap[s] = rid++;
      if(!remap.count(t)) remap[t] = rid++;
      edges.emplace_back(remap[t], remap[s], log((ld)a) - log((ld)b));
    }
  }

  const ld inf = numeric_limits<ld>::infinity();
  vector<ld> dist(rid, inf);
  dist[0] = 0;
  for(int bs=1; bs<rid; bs++) {
    for(auto [i, j, d] : edges) {
      if(dist[i] == inf) continue;
      dist[j] = min(dist[j], dist[i] + d);
    }
  }

  for(auto [i, j, d] : edges) {
    if(dist[i] == inf) continue;
    if(dist[i] + d < dist[j]) {
      cout << "yes" << nl;
      return 0;
    }
  }

  cout << "no" << nl;

  return 0;
}
