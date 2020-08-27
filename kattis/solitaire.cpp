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

map<vector<string>,int> dp;
int solve(vector<string>& g) {
  if(dp.count(g)) return dp[g];
  int res = 0;
  for(int i=0; i<5; i++) {
    for(int j=0; j<9; j++) {
      if(g[i][j] != 'o') continue;
      if(i>=2 && g[i-1][j] == 'o' && g[i-2][j] == '.') {
        swap(g[i][j], g[i-2][j]);
        g[i-1][j] = '.';
        res = max(res, 1 + solve(g));
        g[i-1][j] = 'o';
        swap(g[i][j], g[i-2][j]);
      }
      if(j>=2 && g[i][j-1] == 'o' && g[i][j-2] == '.') {
        swap(g[i][j], g[i][j-2]);
        g[i][j-1] = '.';
        res = max(res, 1 + solve(g));
        g[i][j-1] = 'o';
        swap(g[i][j], g[i][j-2]);
      }
      if(i+2<5 && g[i+1][j] == 'o' && g[i+2][j] == '.') {
        swap(g[i][j], g[i+2][j]);
        g[i+1][j] = '.';
        res = max(res, 1 + solve(g));
        g[i+1][j] = 'o';
        swap(g[i][j], g[i+2][j]);
      }
      if(j+2<9 && g[i][j+1] == 'o' && g[i][j+2] == '.') {
        swap(g[i][j], g[i][j+2]);
        g[i][j+1] = '.';
        res = max(res, 1 + solve(g));
        g[i][j+1] = 'o';
        swap(g[i][j], g[i][j+2]);
      }
    }
  }
  return dp[g] = res;
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

  int T;
  cin >> T;
  while(T--) {
    vector<string> g(5);
    int pegs = 0;
    for(int i=0; i<5; i++) {
      cin >> g[i];
      pegs += count(g[i].begin(), g[i].end(), 'o');
    }
    dp.clear();
    int moves = solve(g);
    cout << pegs - moves << " " << moves << nl;
  }

  return 0;
}
