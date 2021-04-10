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

struct Item {
  ll k; int c;
  Item(ll _k, int _c): k(_k), c(_c) {}
  bool operator < (const Item& o) const {
    return make_pair(c, -k) < make_pair(o.c, -o.k);
  }
};

ostream& operator << (ostream& os, const Item& v) {
  return os << v.k << " " << v.c;
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

  ll n; int d;
  cin >> n >> d;

  Item ans(2, 0);

  if(n < d) {
    cout << ans << nl;
    return 0;
  }

  if(d == 0) {
    for(int j=2; (ll)j*j<=n; j++) {
      int cnt = 0;
      while(n % j == 0) {
        n /= j;
        cnt++;
      }
      if(cnt) {
        ans = max(ans, Item(j, cnt));
      }
    }
    if(n > 1) {
      ans = max(ans, Item(n, 1));
    }

    if(n == 0) {
      ans = max(ans, Item(2, 1));
    }

    cout << ans << nl;
    return 0;
  }

  if(n % d == 0 && n/d-1 > d) {
    ans = max(ans, Item(n/d-1, 2));
  }

  if(n == d) {
    ans = max(ans, Item(d+1, 1));
  }

  for(int j=1; (ll)j*j<=n; j++) {
    if((n-d) % j == 0) {
      if(j > d) {
        ans = max(ans, Item(j, 1));
      }
      if((n-d)/j > d) {
        ans = max(ans, Item((n-d)/j, 1));
      }
    }
  }

  for(int k=d+1; (ll)k*k<=n; k++) {
    int cnt = 2;
    ll sum = 1 + k;
    ll mul = (ll)k*k;
    while(sum*d == n || (sum*d < n && (n-sum*d) % mul == 0)) {
      sum += mul;
      mul *= k;
      cnt++;
    }
    if(cnt > 2) {
      ans = max(ans, Item(k, cnt-1));
    }
  }

  cout << ans << nl;

  return 0;
}
