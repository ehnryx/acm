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

  int n;
  cin >> n;
  int y = 0, e = 0;
  int ty = 0, te = 0;
  int sy = 0, se = 0;
  int ly = 0, le = 0;
  int by = 0, be = 0;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    if(s[0] == 'Y') {
      y++;
      sy++;
      ty++;
      se = 0;
    } else {
      e++;
      se++;
      te++;
      sy = 0;
    }
    by = max(by, sy);
    be = max(be, se);
    ly = max(ly, ty - te);
    le = max(le, te - ty);
  }

  if((by < be) == (ly < le) && (by > be) == (ly > le)) {
    cout << "Agree" << nl;
  } else {
    cout << "Disagree" << nl;
  }

  return 0;
}
