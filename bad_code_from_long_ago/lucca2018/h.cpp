#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

/**
 * Automatically mods everything by MOD
 *
 * egcd(a,b,x,y) calculates x,y that satisfy ax+by=gcd(a,b)
 * to find a^-1 mod m use egcd(a,b,x,y) and x = a^-1
 * egcd also returns the gcd of a and b
 */
ll egcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) { x = 1, y = 0; return a; }
  ll d = egcd(b, a%b, y, x);
  y -= x * (a/b);
  return d;
}
struct Int {
  ll x;
  Int(ll n=0) { x = n % MOD; if (x < 0) x += MOD; }
  operator ll&() { return x; }
  Int operator + (const Int& n) { return Int(x + n.x); }
  Int operator - (const Int& n) { return Int(x - n.x); }
  Int operator * (const Int& n) { return Int(x * n.x); }
  Int operator / (const Int& n) { return Int(x * n.inverse()); }
  Int& operator += (const Int& n) { x = (x + n.x) % MOD; return *this; }
  Int& operator -= (const Int& n) { x = (x + MOD - n.x) % MOD; return *this; }
  Int& operator *= (const Int& n) { x = (x * n.x) % MOD; return *this; }
  Int& operator /= (const Int& n) { x = (x * n.inverse()) % MOD; return *this; }
  ll inverse() const {
    if (x == 0) throw runtime_error("divide by zero");
    ll c, d;
    egcd(x, MOD, c, d);
    return (c+MOD) % MOD;
  }
};
ostream& operator << (ostream& os, const Int& n) {
  os << n.x; return os;
}
////////////////////////////////////////////////////////////////////////

Int part[1001][1001];

void init() {
  for (int i = 2; i <= 1000; i++) {
    part[0][i] = 1;
    for (int j = 1; j <= 1000; j++) {
      part[j][i] = i * part[j-1][i];
    }
  }
}

int solve(int n, int k) {
  k = 2*k + 2;
  if (k > n) return 0;

  Int res = 0;
  for (int i = 0; i < k; i += 2) {
    res += Int(((i%4 == 0) ? 1 : -1) * part[n][k-i] / part[k-i-1][2]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  init();

  int T, n, k;
  cin >> T;
  while (T--) {
    cin >> n >> k;
    cout << solve(n,k) << nl;
  }

  return 0;
}
