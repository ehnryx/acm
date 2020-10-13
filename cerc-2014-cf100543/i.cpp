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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<pair<int,bool>> v;
    vector<ll> sum(2);
    for(int i=0; i<n; i++) {
      int k; char c;
      cin >> k >> c;
      bool w = (c == 'W');
      v.emplace_back(k, w);
      sum[w] += k;
    }

    if(sum[0] == 0) {
      cout << sum[1] << nl;
    } else if(sum[1] == 0) {
      cout << sum[0] << nl;
    } else {
      int ans = 0;
      vector<__int128> cur(2);
      for(auto [a, t] : v) {
        if(cur[!t] * sum[t] % sum[!t] == 0) {
          ll want = cur[!t] * sum[t] / sum[!t] - cur[t];
          if(want > 0 && want <= a) {
            ans++;
            a -= want;
            cur[t] = cur[!t] = 0;
          }
        }
        cur[t] += a;
      }
      cout << ans << nl;
      assert(cur[0] == 0 && cur[1] == 0);
    }
  }

  return 0;
}
