#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "decomp"

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

const ll P = 1789;
const ll M = 1e9+9;

const int N = 5000 + 1;
ll hsh[N], p[N], invp[N];
int dp[N], pre[N];

ll power(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*n % m;
    n = n*n % m;
  }
  return r;
}

ll inverse(ll n, ll m) {
  return power(n, m-2, m);
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

  string s;
  cin >> s;
  int n = s.size();

  for(int i=0; i<n; i++) {
    p[i] = power(P, i, M);
    invp[i] = inverse(p[i], M);
    hsh[i+1] = (hsh[i] + s[i] * p[i]) % M;
  }

  memset(dp, INF, sizeof dp);
  dp[0] = 0;
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<=n; j++) {
      int len = j-i;
      ll rep = (hsh[j] + M - hsh[i]) * invp[i] % M;
      for(int k=j; k<=n; k+=len) {
        ll cur = (hsh[k] + M - hsh[k-len]) * invp[k-len] % M;
        if(cur != rep) break;
        if(dp[i] + len < dp[k]) {
          dp[k] = dp[i] + len;
          pre[k] = i;
        }
      }
    }
  }

  vector<pair<string,int>> ans;
  for(int i=n; i>0; i=pre[i]) {
    int j = pre[i];
    int len = dp[i] - dp[j];
    ans.emplace_back(s.substr(j, len), (i-j)/len);
  }
  reverse(ans.begin(), ans.end());

  cout << dp[n] << nl;
  for(const auto& [t, c] : ans) {
    cout << t << " " << c << nl;
  }

  return 0;
}
