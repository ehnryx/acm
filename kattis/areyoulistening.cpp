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

  int cx, cy, n;
  cin >> cx >> cy >> n;
  vector<tuple<int,int,int>> v;
  for(int i=0; i<n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    v.emplace_back(x, y, r);
  }

  ld l = 0;
  ld r = INF;
  for(int bs=0; bs<200; bs++) {
    ld m = (l + r) / 2;
    int cnt = 0;
    for(auto [x, y, d] : v) {
      cnt += (hypot(x-cx, y-cy) < d + m);
    }
    if(cnt > 2) {
      r = m;
    } else {
      l = m;
    }
  }

  cout << (int)floor(r) << nl;

  return 0;
}
