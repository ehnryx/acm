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

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = gcd(a, b);
    n = a/g; d = b/g;
  }
  bool operator < (const Frac& o) const {
    return n * o.d < d * o.n;
  }
};

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d;
}

const int N = 1e6 + 1;
vector<int> adj[N];
int val[N], plen[N], pcnt[N], vis[N];

pair<int,int> bfs(int s, int t) {
  queue<pair<int,int>> bfs;
  vis[s] = t;
  bfs.emplace(s, 0);
  pair<int,int> last;
  while(!bfs.empty()) {
    auto [u, d] = bfs.front();
    bfs.pop();
    last = pair(d, u);
    for(int v : adj[u]) {
      if(vis[v] == t || val[v] > 1) continue;
      vis[v] = t;
      bfs.emplace(v, d + 1);
    }
  }
  return last;
}

int diameter(int u) {
  return bfs(bfs(u, 1).second, 2).first + 1;
}

int solve_path(int u, int p) {
  int res = 1;
  for(int v : adj[u]) {
    if(v == p || val[v] > 1) continue;
    res = max(res, 1 + solve_path(v, u));
  }
  return res;
}

void solve(int u) {
  for(int v : adj[u]) {
    if(val[v] > 1) continue;
    int len = solve_path(v, u);
    if(len > plen[u]) {
      plen[u] = len;
      pcnt[u] = 0;
    }
    pcnt[u] += (len == plen[u]);
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

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  Frac best(INF);
  for(int i=1; i<=n; i++) {
    cin >> val[i];
    best = min(best, Frac(val[i]));
  }

  for(int i=1; i<=n; i++) {
    if(val[i] == 1) {
      if(vis[i]) continue;
      int d = diameter(i);
      best = min(best, Frac(1, d));
    } else {
      solve(i);
      // TODO this makes the solution quadratic
      // passed on Kattis because weak tests...
    }
  }

  for(int i=1; i<=n; i++) {
    if(val[i] == 1) continue;
    if(pcnt[i] > 1) {
      best = min(best, Frac(val[i], 2*plen[i] + 1));
    }
  }

  cout << best << nl;

  return 0;
}
