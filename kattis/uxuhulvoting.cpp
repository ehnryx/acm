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
    vector<vector<int>> choice(n, vector<int>(9));
    for(int i=0; i<n; i++) {
      for(int j=0; j<8; j++) {
        cin >> choice[i][j];
      }
      choice[i][8] = INF;
    }

    vector<vector<int>> dp(n, vector<int>(8, -1));
    function<int(int,int)> solve = [&](int i, int bm) {
      if(i == n) return bm;
      if(dp[i][bm] != -1) return dp[i][bm];
      int res = 8;
      for(int j=0; j<3; j++) {
        int cur = solve(i+1, bm ^ 1<<j);
        if(choice[i][cur] < choice[i][res]) {
          res = cur;
        }
      }
      return dp[i][bm] = res;
    };

    int ans = solve(0, 0);
    for(int j=0; j<3; j++) {
      if(ans & 1<<(2-j)) {
        cout << 'Y';
      } else {
        cout << 'N';
      }
    }
    cout << nl;
  }

  return 0;
}
