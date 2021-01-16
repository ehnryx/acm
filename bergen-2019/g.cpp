//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5 + 1;
int gdp[N], cap[N];
vector<int> adj[N];

void build(int u, int p) {
  if(p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
  for(int v : adj[u]) {
    build(v, u);
  }
}

pair<ll,ll> solve(int u, ld lb) {
  ll top = gdp[u];
  ll bot = cap[u];
  for(int v : adj[u]) {
    auto [a, b] = solve(v, lb);
    top += a;
    bot += b;
  }
  if((ld)top/bot >= lb) {
    return make_pair(top, bot);
  } else {
    return make_pair(0, 0);
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    cin >> gdp[i];
  }
  for(int i=1; i<=n; i++) {
    cin >> cap[i];
  }
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build(1, 0);

  ld l = (ld) gdp[1] / cap[1];
  ld r = 1e12;
  for(int bs=0; bs<200; bs++) {
    ld v = (l + r) / 2;
    auto [a, b] = solve(1, v);
    if(b) {
      l = v;
    } else {
      r = v;
    }
  }
  cout << r << nl;

  return 0;
}
