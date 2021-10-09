#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
  int a, b;
  bool operator < (const Point& o) const {
    return (a!=o.a ? (a<o.a) : (b<o.b));
  }
  Point operator - (const Point& o) const {
    return { a-o.a, b-o.b };
  }
};

ll power(ll b, ll e) {
  ll r = 1;
  for(;e;e/=2) {
    if(e&1) r = r*b % MOD;
    b = b*b % MOD;
  }
  return r;
}

const int N = 2e5+1;
const int K = 3e3+2;
ll fact[N], invf[N];
ll dp[K];

ll ncr(int n, int r) {
  if(r<0||r>n) return 0;
  return fact[n] * invf[r] % MOD * invf[n-r] % MOD;
}

ll paths(const Point& p) {
  assert(p.a>=0 && p.b>=0);
  return ncr(p.a+p.b, p.a);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  fact[0] = invf[0] = 1;
  for(int i=1;i<N;i++) {
    fact[i] = fact[i-1] * i % MOD;
    invf[i] = power(fact[i], MOD-2);
  }

  int n, m, k;
  cin >> n >> m >> k;
  vector<Point> p;
  for(int i=0;i<k;i++) {
    int a, b;
    cin >> a >> b;
    p.push_back({a,b});
  }
  p.push_back({1,1});
  p.push_back({n,m});
  sort(p.begin(),p.end());

  dp[0] = 1;
  for(int i=1;i<=k+1;i++) {
    ll bad = 0;
    for(int j=1;j<i;j++) {
      Point d = p[i]-p[j];
      if (d.a>=0 && d.b>=0) {
        bad += dp[j] * paths(d) % MOD;
      }
    }
    dp[i] = (paths(p[i]-p[0]) - bad%MOD + MOD) % MOD;
  }
  cout << dp[k+1] << nl;

  return 0;
}
