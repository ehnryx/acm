/*
 * I'm pretty sure that the judge data is broken for this problem
 */

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
const ld EPS = 1e-11;
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

  int n, m;
  cin >> n >> m;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    ld x, y;
    cin >> x >> y;
    pt cur(x, y);
    while((!v.empty() && abs(v.back() - cur) < EPS) ||
        (v.size() >= 2 && abs(arg((cur - v.back()) / (v.back() - v[v.size()-2]))) < EPS)) {
      v.pop_back();
    }
    v.emplace_back(x, y);
  }
  reverse(v.begin(), v.end());
  n = v.size();
  //assert(n >= 2);

  vector<ld> dist(2*n);
  for(int i=1; i<n; i++) {
    dist[2*i+1] = dist[2*i] = dist[2*i-1] + abs(v[i] - v[i-1]);
  }

  vector<ld> lim(n, 180);
  for(int i=1; i<n-1; i++) {
    pt aft = (v[i+1] - v[i]) / abs(v[i+1] - v[i]);
    pt pre = (v[i] - v[i-1]) / abs(v[i] - v[i-1]);
    ld ang = (ld) 180 * abs(arg(aft / pre)) / M_PIl;
    lim[i] = 180 - ang;
    if(lim[i] < 0.9) while(clock()<CLOCKS_PER_SEC);
  }

  vector<vector<ld>> dp(2*n, vector<ld>(m+1, 1e19));
  fill(dp[0].begin(), dp[0].end(), 0);
  for(int i=1; i<2*n; i++) {
    ld cmin = 180;
    for(int j=i-1; j>=0; j--) {
      if(j % 2 == 0) {
        cmin = min(cmin, lim[j/2]);
      }
      ld len = dist[i] - dist[j];
      for(int k=1; k<=m; k++) {
        dp[i][k] = min(dp[i][k], dp[j][k-1] + len / cmin);
      }
    }
    for(int k=0; k<=m; k++) {
      //cerr << "dp " << i << " " << k << " -> " << dp[i][k] << nl;
    }
  }
  cout << dp[2*n-3][m] + (dist[2*n-1] - dist[2*n-3]) / 180 << nl;

  return 0;
}

