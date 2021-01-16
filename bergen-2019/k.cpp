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

int roundup(int n) {
  return (n + 9) / 10 * 10;
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
  vector<int> a(n), order(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> order[i];
  }

  vector<int> sum(n+1);
  partial_sum(a.begin(), a.end(), sum.begin() + 1);

  set<pair<int,int>> segs;
  segs.insert(make_pair(1, n));
  ll chaos = roundup(sum[n]); // total chaos
  ll all = chaos; // sum of all segments
  ll ans = chaos;
  int cnt = 1; // number of segments
  for(int i : order) {
    // cnt * sum_i s_i -> (cnt - 1) * (sum_i s_i - s_j)
    //                  = cnt * sum_i s_i - sum_i s_i - s_j * (cnt - 1)
    // cnt * sum_i s_i -> (cnt + 1) * (sum_i s_i + s_j)
    //                  = cnt * sum_i s_i + sum_i s_i + s_j * (cnt + 1)
    auto it = prev(segs.upper_bound(make_pair(i, n)));
    auto [l, r] = *it;
    // remove segment
    ll cur = roundup(sum[r] - sum[l-1]);
    chaos -= all + cur * (cnt - 1);
    cnt -= 1;
    all -= cur;
    segs.erase(it);
    // add left segment
    if(i > l) {
      ll left = roundup(sum[i-1] - sum[l-1]);
      chaos += all + left * (cnt + 1);
      cnt += 1;
      all += left;
      segs.insert(make_pair(l, i-1));
    }
    // add right segment
    if(i < r) {
      ll right = roundup(sum[r] - sum[i]);
      chaos += all + right * (cnt + 1);
      cnt += 1;
      all += right;
      segs.insert(make_pair(i+1, r));
    }
    ans = max(ans, chaos);
  }
  cout << ans << nl;

  return 0;
}
