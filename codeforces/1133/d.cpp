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

struct Frac {
  ll n, d;
  Frac(ll a, ll b) {
    if (b == 0) {
      n=1; d=0;
    } else {
      ll g = abs(__gcd(a,b));
      n = a/g; d = b/g;
      if (d<0) { d=-d; n=-n; }
    }
  }
  bool operator < (const Frac& o) const {
    return n*o.d < d*o.n;
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

  int n;
  cin >> n;
  int a[n], b[n];
  for (int i=0; i<n; i++) {
    cin >> a[i];
  }

  map<Frac,int> cnt;
  int offset = 0;
  for (int i=0; i<n; i++) {
    cin >> b[i];
    if (a[i] == 0) {
      if (b[i] == 0) {
        offset++;
      }
    } else {
      cnt[Frac(-b[i],a[i])]++;
    }
  }

  int ans = 0;
  for (const auto& it : cnt) {
    ans = max(ans, it.second);
  }
  cout << ans+offset << nl;

  return 0;
}
