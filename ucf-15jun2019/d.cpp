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
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = __gcd(a,b);
    n = a/g; d = b/g;
    if (d < 0) { n=-n; d=-d; }
  }
  bool operator < (const Frac& o) const {
    if (n != o.n) return n < o.n;
    else return d < o.d;
  }
};

const int N = 1e3+1;
ll x[N], y[N];

int solve() {
  int n;
  cin >> n;

  map<Frac,unordered_map<int,int>> cnt;
  map<Frac,unordered_map<int,map<Frac,int>>> dup;
  For(i,n) {
    cin >> x[i] >> y[i];
    For(j,i) {
      Frac slope(x[i]-x[j],y[i]-y[j]);
      ll dist = abs(x[i]-x[j]) + abs(y[i]-y[j]);
      Frac icpt(x[i]);
      if (x[i] != x[j]) {
        icpt = Frac(y[j]*(x[i]-x[j])-x[j]*(y[i]-y[j]),x[i]-x[j]);
      }
      cnt[slope][dist]++;
      dup[slope][dist][icpt]++;
    }
  }

  ll ans = 0;
  for (const auto& it : cnt) {
    for (const auto& jt : it.second) {
      ans += (ll) jt.second * (jt.second-1) / 2;
    }
  }
  for (const auto& it : dup) {
    for (const auto& jt : it.second) {
      for (const auto& kt : jt.second) {
        ans -= (ll) kt.second * (kt.second-1) / 2;
      }
    }
  }
  cout << ans/2 << nl;

  return 0;
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

  int T;
  cin >> T;
  while (T--) {
    assert(solve() == 0);
  }

  return 0;
}
