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

  int n;
  cin >> n;
  int d;
  cin >> d;

  string s;
  cin >> s;
  ll want = 0;
  if(s.find('.') != -1) {
    s.resize(3*n + 2, '0');
    want = stoll(s.substr(2), 0, 2);
  }

  for(int bm=0; bm<1<<n; bm++) {
    ll left = 0;
    ll right = 1LL << (3*n);
    for(int i=0; i<n; i++) {
      ll mid = left + d * (right - left) / 8;
      if(bm & 1<<i) {
        right = mid;
      } else {
        left = mid;
      }
    }
    if(left == want) {
      for(int i=0; i<n; i++) {
        cout << ((bm & 1<<i) ? 'A' : 'B');
      }
      cout << nl;
      return 0;
    }
  }

  assert(false);

  return 0;
}
