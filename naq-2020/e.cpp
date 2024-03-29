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

const int N = 5e5 + 1;
vector<pair<int,int>> adj[N];

ll solve(int u, int p, int down) {
  ll res = 0;
  vector<int> need;
  if(down) need.push_back(down);
  for(auto [v, c] : adj[u]) {
    if(v == p) continue;
    ll add = solve(v, u, c);
    need.push_back(c);
    res += add;
  }

  if(!need.empty()) {
    int big = *max_element(need.begin(), need.end());
    ll sum = accumulate(need.begin(), need.end(), (ll)0);
    if(big > sum - big) {
      res += big;
    } else {
      res += (sum+1)/2;
    }
  }
  return res - down;
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
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  ll ans = solve(0, -1, 0);
  cout << ans << nl;

  return 0;
}
