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

ll solve(vector<pair<int,int>> v, int k) {
  sort(v.begin(), v.end());
  ll res = 0;
  int cur = 0;
  for(int i=(int)v.size()-1; i>=0; i--) {
    if(cur == 0) {
      res += 2 * v[i].first;
    }
    cur += v[i].second;
    if(cur > k) {
      cur -= k;
      res += 2 * v[i].first;
    }
  }
  return res;
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

  int n, k;
  cin >> n >> k;
  vector<pair<int,int>> left, right;
  ll ans = 0;
  for(int i=0; i<n; i++) {
    int x, m;
    cin >> x >> m;
    ans += (m / k) * (ll)abs(x) * 2;
    m %= k;
    if(m > 0) {
      if(x > 0) {
        right.emplace_back(x, m);
      } else if(x < 0) {
        left.emplace_back(-x, m);
      }
    }
  }
  ans += solve(left, k);
  ans += solve(right, k);
  cout << ans << nl;

  return 0;
}
