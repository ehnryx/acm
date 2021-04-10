//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "foreign"

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

  string s;
  cin >> s;
  int n = s.size();
  vector<ld> prob(n + 1), all(n + 1), good(n + 1), bad(n + 1);
  prob[0] = 1;
  all[0] = prob[0] / (n - 0);
  good[0] = (s[0] == 'C' ? prob[0] / (n - 0) : 0);
  bad[0] = (s[0] == 'W' ? prob[0] / (n - 0) : 0);
  for(int i=0; i+1<n; i++) {
    prob[i + 1] = all[i];
    all[i + 1] = all[i] + prob[i + 1] / (n - (i + 1));
    good[i + 1] = good[i] + (s[i + 1] == 'C' ? prob[i + 1] / (n - (i + 1)) : 0);
    bad[i + 1] = bad[i] + (s[i + 1] == 'W' ? prob[i + 1] / (n - (i + 1)) : 0);
    //assert(good[i + 1] + bad[i + 1] == all[i + 1]);
    //cerr << "prob " << i << " -> " << prob[i] << nl;
    //cerr << "bad: " << bad[i] << "  good: " << good[i] << nl;
  }

  ld ans = 0;
  for(int i=0; i<n; i++) {
    if(s[i] == 'C') {
      //cerr << "@ " << i << " -> " << bad[i] << " * " << (n-i) << nl;
      ans += bad[i] * (n - i);
    } else {
      //cerr << "@ " << i << " -> " << good[i] << " * " << (n-i) << nl;
      ans += good[i] * (n - i);
    }
  }
  cout << ans << nl;

  return 0;
}
