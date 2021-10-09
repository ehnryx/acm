#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////
// Extended Euclidean Algorithm (UBC)
// egcd(a,b,x,y) calculates x,y such that ax+by=gcd(a,b)
// To find a^{-1} mod m, use egcd(a,m,x,y), then x = a^{-1}
// Returns gcd(a,b)
//*!
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        ll d = egcd(b, a%b, y, x);
        y -= x * (a/b);
        return d;
    }
}
//*/

////////////////////////////////////////////////////////////////////////
// Int struct for operations on a prime field (TESTED)
// WARNING: slow
//*!
struct Int {
    ll x;
    Int (ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
    operator ll() { return x; }
    Int operator + (const Int& n) const { return Int(x + n.x); }
    Int operator - (const Int& n) const { return Int(x - n.x); }
    Int operator * (const Int& n) const { return Int(x * n.x); }
    Int operator / (const Int& n) const { return Int(x * n.inv()); }
    void operator += (const Int& n) { x = (x + n.x) % MOD; }
    void operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; }
    void operator *= (const Int& n) { x = (x * n.x) % MOD; }
    void operator /= (const Int& n) { x = (x * n.inv()) % MOD; }
    ll inv() const {
        if (x == 0) throw runtime_error("divide by zero");
        ll c, d;
        egcd(x, MOD, c, d);
        return (c < 0) ? c+MOD : c;
    }
};
//*/

////////////////////////////////////////////////////////////////////////
// Disjoint Set Union -- O(a(n)) per query, (inverse ackermann)
// Usage: 
// 1. dsu(n) to create n disjoint sets from 0 to n-1
// 2. dsu.link(i,j) to combine sets containing i and j
// 3. dsu.find(i) to find the root of the set containing i
//*!
struct DSU {
  vector<int> root;
  vector<int> sz;
  DSU(int n) {
    root.resize(n, -1);
    sz.resize(n, 1);
  }
  int find(int i) {
    if (root[i] == -1) return i;
    return root[i] = find(root[i]);
  }
  // returns true if we combine two sets
  bool link(int i, int j) {
    i = find(i);
    j = find(j);
    if (i == j) return false;
    if (sz[i] < sz[j]) swap(i,j);
    root[j] = i;
    sz[i] += sz[j];
    return true;
  }
  int size(int i) {
    return sz[find(i)];
  }
};
//*/

const int N = 1e5+1;
Int fact[N];
Int invf[N];

void init() {
  fact[0] = invf[0] = 1;
  for (int i=1; i<N; i++) {
    fact[i] = Int(i)*fact[i-1];
    invf[i] = fact[i].inv();
  }
}

Int ncr(int n, int r) {
  return fact[n] * invf[r] * invf[n-r];
}

Int f(int t, int v) {
  Int b = v;
  Int res = fact[t-1];
  for (int i=t-1; i>0; i/=2) {
    if (i%2 == 1) res *= b;
    b *= b;
  }
  return res;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif
  init();

  int n, k;
  cin >> n >> k;

  DSU dsu(n+1);
  vector<int> a(n+1);
  for (int i=1; i<=n; i++) {
    cin >> a[i];
    dsu.link(i,a[i]);
  }

  vector<int> cnt(n+1, 0);
  for (int i=1; i<=n; i++) {
    cnt[dsu.size(i)]++;
  }

  Int ans = 1;
  for (int i=1; i<=n; i++) {
    if (!cnt[i]) continue;
    int m = cnt[i]/i;
    //cerr << "SOLVE " << m << " groups of " << i << nl;

    // find transitions
    vector<int> trans;
    for (int j=1; j<=m; j++) {
      if (__gcd(k, j*i) == j) {
        //cerr << "transition: " << j << nl;
        trans.push_back(j);
      }
    }

    // solve dp
    vector<Int> dp(m+1, 0);
    dp[0] = 1;
    for (int j=0; j<m; j++) {
      for (int t : trans) {
        if (j+t <= m) {
          dp[j+t] += ncr(j+t-1,t-1) * dp[j] * f(t,i);
        }
      }
    }
    ans *= dp[m];
    //cerr << dp[m] << " for case " << i << nl;
    //cerr << nl;
  }

  cout << ans << nl;

  return 0;
}
