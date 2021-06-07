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

  const int n = 10;
  vector<int> a(n), r(n);
  for(int i=0; i<n; i++) {
    cin >> a[i] >> r[i];
  }
  vector<int> s(n), len(n), rest(n);
  for(int i=0; i<n; i++) {
    cin >> len[i] >> rest[i] >> s[i];
  }

  int cur = 0;
  for(int round=0; round<3; round++) {
    for(int i=0; i<n; i++) {
      int at = (cur - s[i]) % (len[i] + rest[i]);
      if(at < 0) at += len[i] + rest[i];
      if(cur >= s[i] && at < len[i]) {
        cur += len[i] - at;
        at = len[i];
      }
      if(s[i] < cur + a[i] && at + a[i] > len[i] + rest[i]) {
        s[i] = cur + a[i];
      }
      cur += a[i] + r[i];
    }
  }
  cout << cur - r.back() << nl;

  return 0;
}
