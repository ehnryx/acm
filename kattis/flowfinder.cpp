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

const int N = 3e5 + 1;
int par[N];
vector<int> adj[N];

ll flow[N];

pair<ll,int> solve(int u) {
  ll cur = 0;
  int bad = 0;
  int badv = 0;
  for(int v : adj[u]) {
    auto [val, x] = solve(v);
    bad += x;
    if(x) {
      badv = v;
    } else {
      cur += val;
    }
  }

  if(bad > 1) {
    return make_pair(0, bad);
  }

  if(adj[u].empty()) {
    return make_pair(flow[u], !flow[u]);
  }

  if(flow[u] == 0) {
    if(bad == 0) {
      flow[u] = cur;
      //cerr << "set flow " << u << " to " << cur << nl;
      return make_pair(cur, 0);
    } else {
      return make_pair(cur, 1);
    }
  } else {
    if(bad == 0) {
      if(flow[u] != cur) {
        return make_pair(0, 2);
      } else {
        return make_pair(cur, 0);
      }
    } else {
      if(flow[u] <= cur) {
        return make_pair(0, 2);
      } else {
        flow[badv] = flow[u] - cur;
        //cerr << "set flow " << badv << " to " << flow[u] << " - " << cur << nl;
        return make_pair(flow[u], 0);
      }
    }
  }
  assert(false);
}

void solve_down(int u) {
  ll cur = 0;
  int badv = 0;
  for(int v : adj[u]) {
    if(flow[v] == 0) {
      badv = v;
    } else {
      cur += flow[v];
    }
  }
  if(badv) {
    //cerr << "set flow " << badv << " to " << flow[u] << " - " << cur << nl;
    flow[badv] = flow[u] - cur;
  }

  for(int v : adj[u]) {
    solve_down(v);
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
  for(int i=2; i<=n; i++) {
    cin >> par[i];
    adj[par[i]].push_back(i);
  }
  for(int i=1; i<=n; i++) {
    cin >> flow[i];
  }

  auto [_, bad] = solve(1);
  solve_down(1);
  if(bad || *min_element(flow+1, flow+1+n) <= 0) {
    cout << "impossible" << nl;
  } else {
    for(int i=1; i<=n; i++) {
      cout << flow[i] << nl;
    }
  }

  return 0;
}
