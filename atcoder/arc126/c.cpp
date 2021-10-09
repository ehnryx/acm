#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

  int n; ll k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  int big = *max_element(begin(a), end(a));
  ll need = 0;
  vector<ll> sum(2*big+1), freq(2*big+1);
  for(int i=0; i<n; i++) {
    need += big - a[i];
    sum[a[i]] += a[i];
    freq[a[i]] += 1;
  }
  partial_sum(begin(sum), end(sum), begin(sum));
  partial_sum(begin(freq), end(freq), begin(freq));

  if(need <= k) {
    cout << big + (k - need) / n << nl;
    return 0;
  }

  int ans = 1;

  // otherwise gcd < big
  static const int S = 600;
  for(int g=2; g<S; g++) {
    ll cnt = 0;
    for(int i=0; i<n; i++) {
      int rem = a[i] % g;
      if(rem) {
        cnt += g - rem;
      }
    }
    if(cnt <= k) {
      ans = g;
    }
  }

  for(int i=S; i<big; i++) {
    ll cnt = 0;
    for(int j=0; j*i<big; j++) {
      // get range [j*i, (j+1)*i)
      int l = j * i;
      int r = (j+1) * i;
      ll have = sum[r - 1] - sum[l];
      cnt += (freq[r - 1] - freq[l]) * r - have;
    }
    if(cnt <= k) {
      ans = i;
    }
  }

  cout << ans << nl;

  return 0;
}
