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

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  }
  return r;
}

int add(int a, int b) {
  return a+b < MOD ? a+b : a+b-MOD;
}

vector<int> solve(const vector<ll>& a) {
  int n = size(a);

  const int L = 32 - __builtin_clz(n);
  vector jump(L, vector<ll>(n+1));
  for(int i=0; i<n; i++) {
    jump[0][i] = a[i];
  }
  for(int j=1; j<L; j++) {
    for(int i=0; i+(1<<j)<=n; i++) {
      jump[j][i] = jump[j-1][i] & jump[j-1][i+(1<<(j-1))];
    }
  }

  vector<int> dp(n+1), prefix(n+1);
  dp[0] = 1;
  prefix[0] = 1;
  for(int i=1; i<=n; i++) {
    int l = 0;
    int r = i-1;
    while(l < r) {
      int m = (l+r) / 2;
      int j = 31 - __builtin_clz(i - m);
      if(jump[j][m] & jump[j][i-(1<<j)]) {
        r = m;
      } else {
        l = m+1;
      }
    }
    dp[i] = add(prefix[i-1], r > 0 ? MOD - prefix[r-1] : 0);
    prefix[i] = add(prefix[i-1], dp[i]);
  }
  return dp;
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

  int n;
  cin >> n;
  vector<ll> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  if(accumulate(begin(a), end(a), (1LL<<60) - 1, bit_and<ll>())) {
    cout << add(modpow(2, n, MOD), MOD - n) << nl;
    return 0;
  }

  int ans = 0;
  while(a[0]) {
    vector<int> dp = solve(a);
    ll cur = a[0];
    while(a[0] == cur) {
      ans = add(ans, dp[n--]);
      a[0] &= a.back();
      a.pop_back();
    }
  }
  cout << ans << nl;

  return 0;
}
