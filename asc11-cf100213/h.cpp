//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "princess"

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

const int N = 51;
int dp[N][N][N];
pair<int,int> pre[N][N][N];

bool update(int& x, int v) {
  x = max(x, v);
  return x == v;
}

void recover(int n, int j, int k) {
  string ans;
  for( ; n > 0; n--) {
    auto [nj, nk] = pre[n][j][k];
    if(nj == j) ans.push_back('E');
    else ans.push_back('D');
    j = nj;
    k = nk;
  }
  reverse(ans.begin(), ans.end());
  cout << ans << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, h, s, p, m;
  cin >> n >> h >> s >> p >> m;

  dp[0][0][0] = h;
  for(int i=1; i<=n; i++) {
    int si, pi, mi;
    cin >> si >> pi >> mi;
    for(int j=0; j<=i; j++) {
      for(int k=0; k<=m; k++) {
        // defeat
        if(j > 0 && s + j-1 >= si) {
          int dmg = max(0, 2*si - (s+j-1));
          if(update(dp[i][j][k], dp[i-1][j-1][k] - dmg)) {
            pre[i][j][k] = make_pair(j-1, k);
          }
        }
        // enchant
        if(j < i && p + i-1-j >= pi && mi <= k) {
          if(update(dp[i][j][k], dp[i-1][j][k-mi])) {
            pre[i][j][k] = make_pair(j, k-mi);
          }
        }
      }
    }
  }

  for(int j=0; j<=n; j++) {
    for(int k=0; k<=m; k++) {
      if(dp[n][j][k]) {
        recover(n, j, k);
        return 0;
      }
    }
  }

  cout << "UNLUCKY" << nl;

  return 0;
}
