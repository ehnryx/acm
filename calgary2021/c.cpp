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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  int na, nb, nc;
  cin >> na >> nb >> nc;
  vector<int> a(na), b(nb), c(nc);
  for(int i=0; i<na; i++) {
    cin >> a[i];
  }
  for(int i=0; i<nb; i++) {
    cin >> b[i];
  }
  for(int i=0; i<nc; i++) {
    cin >> c[i];
  }

  int ans = max(a.size(), max(b.size(), c.size()));
  vector<int> ab, bc, ca;
  set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(ab));
  set_intersection(b.begin(), b.end(), c.begin(), c.end(), back_inserter(bc));
  set_intersection(c.begin(), c.end(), a.begin(), a.end(), back_inserter(ca));

  vector<int> ab_bc, abc;
  set_union(ab.begin(), ab.end(), bc.begin(), bc.end(), back_inserter(ab_bc));
  set_union(ab_bc.begin(), ab_bc.end(), ca.begin(), ca.end(), back_inserter(abc));
  ans = max(ans, (int)abc.size());

  cout << ans << nl;

  return 0;
}
