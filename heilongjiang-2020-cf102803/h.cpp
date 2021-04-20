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

using ull = unsigned long long;

ull power(ull d, int k) {
  ull r = 1;
  while(k--) {
    r *= d;
  }
  return r;
}

ull sum(ull n, int k) {
  if(k == 0) {
    return n;
  } else if(k == 1) {
    ull a = n;
    ull b = n+1;
    if(a % 2 == 0) a /= 2;
    else b /= 2;
    return a * b;
  } else if(k == 2) {
    ull a = n;
    ull b = n+1;
    ull c = 2*n + 1;
    if(a % 2 == 0) a /= 2;
    else b /= 2;
    if(a % 3 == 0) a /= 3;
    else if(b % 3 == 0) b /= 3;
    else c /= 3;
    return a * b * c;
  } else {
    ull a = n;
    ull b = n+1;
    if(a % 2 == 0) a /= 2;
    else b /= 2;
    return a * a * b * b;
  }
}

ull calc(ull n, int k) {
  ull s = sqrt(n);
  ull ans = 0;
  for(ull d=1; n/d>=s; d++) {
    ans += n/d * power(d, k);
  }
  for(ull v=1; v<s; v++) {
    ans += v * (sum(n/v, k) - sum(n/(v+1), k));
  }
  return ans;
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

  int a, b; ull n;
  cin >> a >> b >> n;
  cout << (calc(n, a) ^ calc(n, b)) << nl;

  return 0;
}
