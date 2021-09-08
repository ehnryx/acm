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

namespace ubc {
  using vi = vector<ll>;
  using pii = pair<ll, ll>;
  void FST(vi& a, bool inv) {
    for (int n = a.size(), step = 1; step < n; step *= 2) {
      for (int i=0; i<n; i += 2 * step) for (int j=i; j<i+step; j++) {
        ll &u = a[j], &v = a[j + step]; tie(u, v) =
          // inv ? pii(v - u, u) : pii(v, u + v); // AND
          // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
          pii(u + v, u - v);                   // XOR /// include-line
      }
    }
    if (inv) for (auto& x : a) x /= a.size(); // XOR only /// include-line
  }
  vi conv(vi a, vi b) {
    FST(a, 0); FST(b, 0);
    for (int i = 0; i < a.size(); i++) a[i] *= b[i];
    FST(a, 1); return a;
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

  int n, m; ll k;
  cin >> n >> m >> k;

  vector<ll> cnt(1<<m);
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    int bm = 0;
    for(char c : s) {
      bm = bm << 1 | (c - 'A');
    }
    cnt[bm] += 1;
  }

  cnt = ubc::conv(cnt, cnt);
  cnt[0] = 0;
  for(int bm=1; bm<1<<m; bm++) {
    assert(cnt[bm] % 2 == 0);
    cnt[bm] /= 2;
  }

  vector<ll> sum = cnt;
  for(int j=0; j<m; j++) {
    for(int bm=0; bm<1<<m; bm++) {
      if(bm & 1<<j) {
        sum[bm] += sum[bm ^ 1<<j];
      }
    }
  }

  ll total = accumulate(begin(cnt), end(cnt), (ll)0);

  int ans = 0;
  for(int bm=0; bm<1<<m; bm++) {
    if(total - sum[bm] >= k) {
      ans += 1;
    }
  }
  cout << ans << nl;

  return 0;
}
