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
  //ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int xa, ya, xb, yb, xc, yc;
  cin >> xa >> ya >> xb >> yb >> xc >> yc;
  swap(xb, xc); swap(yb, yc);
  pt A(xa, ya), B(xb, yb), C(xc, yc);

  pair<ld,string> ans(INF, "eyqs");

  int d, v;
  cin >> d >> v;
  ans = min(ans, make_pair((abs(A-B) + abs(B-C)) / v * 60 + d, string("Alex")));

  int dh, dm, th, tm;
  scanf("%d:%d %d:%d", &dh, &dm, &th, &tm);
  int ah = dh + th;
  int am = dm + tm;
  while(am >= 60) {
    ah += 1;
    am -= 60;
  }
  ans = min(ans, make_pair((ah - 9) * 60 + (ld)am, string("Dmitry")));

  int w;
  cin >> w;
  if((xa-xb)*(yb-yc) == (ya-yb)*(xb-xc)) {
    ans = min(ans, make_pair(abs(A-C) / w * 60 + d, string("Petr")));
    cerr << "here" << nl;
  } else {
    ans = min(ans, make_pair(abs(A-C) / w * 60, string("Petr")));
  }

  cout << ans.second << nl;

  return 0;
}
