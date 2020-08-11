//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "ssh"

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

const int N = 100 + 1;
const int M = 26;
string dp[N][M];
int val[N][M];

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

  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for(int i=1; i<n; i++) {
    cin >> a[i];
  }

  int t[m][m];
  for(int i=0; i<m; i++) {
    for(int j=0; j<m; j++) {
      cin >> t[i][j];
    }
  }

  for(int i=0; i<m; i++) {
    dp[0][i].push_back(i + 'a');
    val[0][i] = 0;
  }
  for(int i=1; i<n; i++) {
    for(int j=0; j<m; j++) {
      int best = 0;
      for(int k=1; k<m; k++) {
        if(val[i-1][k] + abs(t[k][j] - a[i]) < val[i-1][best] + abs(t[best][j] - a[i])) {
          best = k;
        }
      }
      dp[i][j] = dp[i-1][best];
      dp[i][j].push_back(j + 'a');
      val[i][j] = val[i-1][best] + abs(t[best][j] - a[i]);
    }
  }

  int best = min_element(val[n-1], val[n-1] + m) - val[n-1];
  cout << dp[n-1][best] << nl;

	return 0;
}
