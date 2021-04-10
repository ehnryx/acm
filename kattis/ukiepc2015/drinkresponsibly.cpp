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
random_device _rd; mt19937 rng(_rd());

int read(int mul) {
  ld v;
  cin >> v;
  return round(v * mul);
}

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

  int m = read(100);
  int u = read(60);
  int n;
  cin >> n;
  vector dp(n+1, vector(m+1, vector<pair<int,int>>(u+1, pair(-1, -1))));
  dp[0][0][0] = pair(0, 0);

  vector<string> name(n+1);
  vector<int> cost(n+1);
  for(int i=1; i<=n; i++) {
    cin >> name[i];
    int strength;
    cin >> strength;
    string sz;
    cin >> sz;
    strength *= 10 * (sz.back() == '1' ? 6 : sz.back() == '2' ? 3 : 2);
    cost[i] = read(100);

    for(int j=0; j<=m; j++) {
      for(int k=0; k<=u; k++) {
        for(int c=0; c*cost[i] <= j && c*strength <= k; c++) {
          int pj = j - c * cost[i];
          int pk = k - c * strength;
          if(dp[i-1][pj][pk] == pair(-1, -1)) continue;
          dp[i][j][k] = pair(pj, pk);
          break;
        }
      }
    }
  }

  if(dp[n][m][u] == pair(-1, -1)) {
    cout << "IMPOSSIBLE" << nl;
  } else {
    for(int i=n, j=m, k=u; i>0; i--) {
      int cnt = (j - dp[i][j][k].first) / cost[i];
      if(cnt) {
        cout << name[i] << " " << cnt << nl;
      }
      tie(j, k) = dp[i][j][k];
    }
  }


  return 0;
}
