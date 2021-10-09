#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

const int N = 1 << 19;
const Int half = Int(2).inverse();
Int coeff[N];

ll sum[2*N];
Int ans[2*N];

void pull(int i, int lcnt, int rcnt) {
  sum[i] = sum[2*i] + sum[2*i+1];
  ans[i] = ans[2*i] + ans[2*i+1];
  Int lavg = Int(sum[2*i]) / lcnt;
  Int ravg = Int(sum[2*i+1]) / rcnt;
  Int diff = sum[2*i]*rcnt < sum[2*i+1]*lcnt ? ravg - lavg : lavg - ravg;
  if(lcnt == rcnt) {
    ans[i] += diff * half * rcnt;
  } else {
    assert(lcnt == rcnt + 1);
    ans[i] += diff * half * rcnt;
    ans[i] += diff * half * coeff[2*rcnt];
  }
}

void build(const vector<int>& a, int i, int s, int e) {
  if(s == e) {
    sum[i] = a[s];
    ans[i] = 0;
    return;
  }
  int m = (s+e) / 2;
  build(a, 2*i, s, m);
  build(a, 2*i+1, m+1, e);
  pull(i, m-s+1, e-m);
}

void update(int j, int v, int i, int s, int e) {
  if(s == e) {
    sum[i] = v;
    return;
  }
  int m = (s+e) / 2;
  if(j <= m) update(j, v, 2*i, s, m);
  else update(j, v, 2*i+1, m+1, e);
  pull(i, m-s+1, e-m);
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

  coeff[1] = half;
  for(int i=2; i<N; i++) {
    coeff[i] = (coeff[i-1] + 1) / (Int(2) - Int(i-1) / Int(i));
  }

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  build(a, 1, 0, n-1);

  for(int i=0; i<m; i++) {
    int j, v;
    cin >> j >> v;
    update(j-1, v, 1, 0, n-1);
    cout << ans[1] << nl;
  }

  return 0;
}
