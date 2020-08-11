//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "lottery"

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

struct Frac {
  ll n, d;
  Frac(ll a, ll b) {
    ll g = abs(__gcd(a, b)) * (b<0 ? -1 : 1);
    n = a/g;
    d = b/g;
  }
};

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d;
}

const int N = 60 + 1;
const int M = 26 + 1;
ll ncr[N][N];
ll dp[M][N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  for(int i=0; i<N; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
    }
  }

  int n;
  cin >> n;
  string s;
  cin >> s;
  int m = s.size();
  sort(s.begin(), s.end());

  string t = s;
  t.resize(unique(t.begin(), t.end()) - t.begin());

  vector<int> f;
  for(char c : t) {
    f.push_back(count(s.begin(), s.end(), c));
  }
  sort(f.begin(), f.end());

  int only = m - f[0];
  Frac small(ncr[n-only][f[0]], ncr[n][m]);

  dp[0][0] = 1;
  for(int i=0; i<f.size(); i++) {
    for(int j=f[i]; j<=n; j++) {
      for(int k=f[i]; k<=j; k++) {
        dp[i+1][j] = max(dp[i+1][j], dp[i][j-k] * ncr[k][f[i]]);
      }
    }
  }
  Frac big(dp[f.size()][n], ncr[n][m]);

  cout << big << nl;
  cout << small << nl;

  return 0;
}
