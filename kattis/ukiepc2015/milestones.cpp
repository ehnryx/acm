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

  int m, n;
  cin >> m >> n;
  vector<ll> a(m), b(n);
  for(int i=0; i<m; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> b[i];
  }

  set<ll> all;
  for(int s=0; s+m<=n; s++) {
    ll d = b[s+1] - b[s];
    ll t = a[1] - a[0];
    bool ok = true;
    for(int i=2; i<m && ok; i++) {
      ok &= (__int128)(b[s+i] - b[s+i-1]) * t == (__int128)(a[i] - a[i-1]) * d;
    }
    if(ok) {
      all.insert(d);
    }
  }

  cout << all.size() << nl;
  for(ll x : all) {
    cout << x << " ";
  }
  cout << nl;

  return 0;
}
