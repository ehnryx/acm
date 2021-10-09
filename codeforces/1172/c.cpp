#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+1;
bool good[N]; 
ll val[N], p[N];

ll power(ll x, int e) {
  ll res = 1;
  for (; e>0; e/=2) {
    if (e&1) res = res*x % MOD;
    x = x*x % MOD;
  }
  return res;
}

ll inv(ll x) {
  return power(x, MOD-2);
}

struct Int {
  ll n, d;
  Int(ll a, ll b) {
    n = a%MOD;
    d = b%MOD;
  }
  Int operator + (const Int& o) const {
    return Int(n*o.d + d*o.n, d*o.d);
  }
  Int operator * (const Int& o) const {
    return Int(n*o.n, d*o.d);
  }
  Int operator / (const Int& o) const {
    return Int(n*o.d, d*o.n);
  }
  ll value() const {
    return n*inv(d);
  }
  ld eval() const {
    return (ld)n/d;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  For(i,n) {
    cin >> good[i];
  }

  ll sum = 0;
  For(i,n) {
    cin >> val[i];
    sum += val[i];
  }

  ll invsum = inv(sum);
  ll pp = 0;
  ll pm = 0;
  For(i,n) {
    p[i] = val[i] * invsum;
    if (good[i]) {
    }
  }

  For(i,m) {
    For(j,n) {
      if (good[j]) {
        val[j] = (val[j] + p[j]) % MOD;
        p[j] = (p[j] * (p[j]+
      } else {
        val[j] = (val[j] - p[j]) % MOD;
      }
    }
  }

  For(i,n) {
    cout << (val[i]+MOD) % MOD << nl;
  }

  return 0;
}
