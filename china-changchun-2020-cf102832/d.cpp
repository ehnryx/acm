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
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

const int N = 3000 + 7;
ll ncr[N][N];

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

  for(int i=0; i<N; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % MOD;
    }
  }

  string s;
  cin >> s;
  int c;
  cin >> c;

  int len = size(s);
  vector<int> ones;
  for(int i=0; i<len; i++) {
    if(s[i] == '1') ones.push_back(i);
  }
  int o = size(ones);

  ll ans = 1;
  for(int n=1; n<=len; n++) {
    ll cnt = (n <= o);
    for(int fix=0; fix <= min(n-1, o-1); fix++) {
      cnt += ncr[len - ones[fix] - 1][n - fix];
    }
    ans += cnt % MOD * modpow(c, n, MOD) % MOD;
  }
  ans %= MOD;
  cout << ans << nl;

  return 0;
}
