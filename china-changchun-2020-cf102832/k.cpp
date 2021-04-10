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

const int M = 2e5 + 1;
const int N = 3e5 + 1;
vector<int> adj[M];
int dsu[N], val[N];
unordered_map<int,int> have[N];

ll ans = 0;

int find(int i) {
  if(dsu[i] == 0) return i;
  return dsu[i] = find(dsu[i]);
}

void link(int i, int j) {
  i = find(i); j = find(j);
  if(i == j) return;
  if(size(have[i]) > size(have[j])) swap(i, j);
  for(auto [v, c] : have[i]) {
    for(int o : adj[v]) {
      if(!have[j].count(o)) continue;
      ans += (ll)c * have[j][o];
    }
  }
  dsu[i] = j;
  for(auto [v, c] : have[i]) {
    have[j][v] += c;
  }
}

void change(int x, int v) {
  int r = find(x);
  for(int j : adj[val[x]]) {
    if(!have[r].count(j)) continue;
    ans -= have[r][j];
  }
  if(--have[r][val[x]] == 0) {
    have[r].erase(val[x]);
  }
  val[x] = v;
  have[r][val[x]] += 1;
  for(int j : adj[val[x]]) {
    if(!have[r].count(j)) continue;
    ans += have[r][j];
  }
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

  for(int i=1; i<M; i++) {
    for(int d=1; d*d<=i; d++) {
      if(i % d) continue;
      for(int g : d*d < i ? vector({d, i/d}) : vector({d})) {
        int j = i ^ g;
        if(0 < j && j < M && gcd(i, j) == g) {
          adj[i].push_back(j);
        }
      }
    }
  }

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    cin >> val[i];
    have[i][val[i]] += 1;
  }

  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int x, v;
      cin >> x >> v;
      val[x] = v;
      have[x][val[x]] += 1;
    } else if(t == 2) {
      int x, y;
      cin >> x >> y;
      link(x, y);
    } else if(t == 3) {
      int x, v;
      cin >> x >> v;
      change(x, v);
    } else {
      assert(false);
    }
    cout << ans << nl;
  }

  return 0;
}
