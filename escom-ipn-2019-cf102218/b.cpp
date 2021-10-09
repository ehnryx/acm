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

// Find x,y such that ax + by = d = gcd(a,b)
// * a^-1 (mod m): if (egcd(a,m,x,y) == 1) return (x+m)%m; else ERROR;
ll egcd(ll a, ll b, ll& x, ll &y) {
  if (!b) {x = 1; y = 0; return a;}//to ensure d>=0: x=sgn(a);y=0;return abs(a);
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d;
}

struct Int {
  ll x;
  Int(ll v=0) { x=v%MOD; if (x<0) x+=MOD; }
  Int operator + (const Int& o) const { return Int(x + o.x); }
  Int operator - (const Int& o) const { return Int(x - o.x); }
  Int operator * (const Int& o) const { return Int(x * o.x); }
  Int inv() const {
    ll res, _;
    egcd(x,MOD,res,_);
    return Int(res);
  }
};

Int power(Int b, int e) {
  Int res(1);
  for ( ; e>0; e/=2) {
    if (e&1) res = res * b;
    b = b * b;
  }
  return res;
}

const int N = 1<<17;
const int L = 30;
Int invN = Int(N).inv();
Int a[L][N];
Int ans[N];

template<class T>
void fwht(T p[], bool inv = false) {
  for (int len=1; 2*len<=N; len*=2) {
    for (int i=0; i<N; i+=2*len) {
      for (int j=0; j<len; j++) {
        T u = p[i+j];
        T v = p[i+len+j];
        p[i+j] = u+v;
        p[i+len+j] = u-v;
      }
    }
  }
  if (inv) {
    For(i,N) {
      p[i] = p[i] * invN;
    }
  }
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

  int m, k;
  cin >> m >> k;

  For(i,k) {
    int v;
    cin >> v;
    a[0][v] = Int(1);
  }
  fwht(a[0]);

  for (int j=1; j<L; j++) {
    For(i,N) {
      a[j][i] = a[j-1][i] * a[j-1][i];
    }
  }

  ans[0] = Int(1);
  fwht(ans);

  Int base = power(Int(k),m);
  for (int j=0; m>0; m/=2, j++) {
    if (m&1) {
      For(i,N) {
        ans[i] = ans[i] * a[j][i];
      }
    }
  }
  fwht(ans, true);

  ll sum = 0;
  FOR(i,1,N-1) {
    sum += ans[i].x;
  }
  cout << (Int(sum)*base.inv()).x << nl;

  return 0;
}
