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

const int L = 20;
const int N = 1e5 + 1;
vector<int> adj[N];
vector<int> sub[N];
int val[N];

unordered_map<int,array<int,L+1>> bits[N];

ll solve(int u, int p) {
  ll res = 0;
  for(int v : adj[u]) {
    if(v == p) continue;
    res += solve(v, u);
  }

  for(int i=0; i<L; i++) {
    if(u & 1<<i) {
      bits[u][val[u]][i] += 1;
    }
  }
  bits[u][val[u]][L] += 1;
  sub[u].push_back(u);

  for(int v : adj[u]) {
    if(v == p) continue;
    if(size(sub[u]) < size(sub[v])) {
      swap(sub[u], sub[v]);
      swap(bits[u], bits[v]);
    }
    for(int i : sub[v]) {
      int want = val[i] ^ val[u];
      if(!bits[u].count(want)) continue;
      for(int j=0; j<L; j++) {
        if(i & 1 << j) {
          res += (bits[u][want][L] - (ll)bits[u][want][j]) << j;
        } else {
          res += (ll)bits[u][want][j] << j;
        }
      }
    }
    for(const auto& [key, _] : bits[v]) {
      for(int j=0; j<=L; j++) {
        bits[u][key][j] += bits[v][key][j];
      }
    }
    sub[u].insert(end(sub[u]), begin(sub[v]), end(sub[v]));
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

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    cin >> val[i];
  }
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  ll ans = solve(1, 0);
  cout << ans << nl;

  return 0;
}
