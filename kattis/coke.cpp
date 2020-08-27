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

const int N = 150 + 1;
const int M = 700 + 1;
const int K = 150 + 1;
int dp[N][M][K];

int solve(int n, int a, int b) {
  if(dp[n][a][b] != -1) return dp[n][a][b];
  if(n == 0) return dp[n][a][b] = 0;
  int res = INF;
  if(a >= 8) res = min(res, 8 + solve(n-1, a-8, b));
  if(a >= 3 && b >= 1) res = min(res, 4 + solve(n-1, a-3, b-1));
  if(b >= 2) res = min(res, 2 + solve(n-1, a+2, b-2));
  assert(res != INF);
  return dp[n][a][b] = res;
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

  memset(dp, -1, sizeof dp);

  int T;
  cin >> T;
  while(T--) {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int ans = INF;
    int tens = min(n, c);
    for(int i=0; i<=tens; i++) {
      if(a < 3*i) continue;
      int cur = tens-i + 4*i;
      ans = min(ans, cur + solve(n-tens, a-3*i + 2*(tens-i), b+i));
    }
    cout << ans << nl;
  }

  return 0;
}
