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
  reverse(order.begin(), order.end());

  vector<int> sum(n+1);
  partial_sum(a.begin(), a.end(), sum.begin() + 1);

  vector<int> dsu(n+1), left(n+1), right(n+1);
  iota(left.begin(), left.end(), 0);
  iota(right.begin(), right.end(), 0);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == 0) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if(i == j) return;
    dsu[i] = j;
    left[j] = min(left[i], left[j]);
    right[j] = max(right[i], right[j]);
  };

  ll chaos = 0; // total chaos
  ll all = 0; // sum of all segments
  int cnt = 0; // number of segments
  ll ans = 0;

  vector<bool> have(n + 2);
  for(int i : order) {
    // remove a segment:
    // cnt * sum_i s_i -> (cnt - 1) * (sum_i s_i - s_j)
    //                  = cnt * sum_i s_i - sum_i s_i - s_j * (cnt - 1)
    // add a segment:
    // cnt * sum_i s_i -> (cnt + 1) * (sum_i s_i + s_j)
    //                  = cnt * sum_i s_i + sum_i s_i + s_j * (cnt + 1)
    have[i] = true;
    if(have[i-1]) {
      ll cur = roundup(sum[right[find(i-1)]] - sum[left[find(i-1)] - 1]);
      chaos -= all + cur * (cnt - 1);
      all -= cur;
      cnt -= 1;
      link(i, i-1);
    }
    if(have[i+1]) {
      ll cur = roundup(sum[right[find(i+1)]] - sum[left[find(i+1)] - 1]);
      chaos -= all + cur * (cnt - 1);
      all -= cur;
      cnt -= 1;
      link(i, i+1);
    }
    ll cur = roundup(sum[right[find(i)]] - sum[left[find(i)] - 1]);
    chaos += all + cur * (cnt + 1);
    all += cur;
    cnt += 1;
    ans = max(ans, chaos);
  }
  cout << ans << nl;

  return 0;
}
