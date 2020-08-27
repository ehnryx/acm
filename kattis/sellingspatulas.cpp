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
  cout << fixed << setprecision(2);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(int n; cin >> n && n; ) {
    vector<int> t(n+1);
    vector<int> v(n+1);
    for(int i=1; i<=n; i++) {
      ld val;
      cin >> t[i] >> val;
      v[i] = round(val * 100);
    }
    partial_sum(v.begin(), v.end(), v.begin());

    int best = 0;
    pair<int,int> ans(-1, -1);
    for(int i=1; i<=n; i++) {
      for(int j=i; j<=n; j++) {
        int cur = v[j] - v[i-1] - (t[j]-t[i]+1)*8;
        if(cur > best) {
          best = cur;
          ans = make_pair(t[i], t[j]);
        } else if(cur == best && t[j] - t[i] < ans.second - ans.first) {
          ans = make_pair(t[i], t[j]);
        }
      }
    }

    if(best == 0) {
      cout << "no profit" << nl;
    } else {
      cout << (ld)best/100 << " " << ans.first << " " << ans.second << nl;
    }
  }

  return 0;
}
