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

ll sqr(ll x) { return x*x; }

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

  while (n--) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll ans = 0;
    for (int i=0; i<42; i++) {
      for (int j=0; j<42; j++) {
        if (i+j>d) continue;
        int k = d-i-j;
        ans = max(ans, sqr(a+i)+sqr(b+j)+sqr(c+k)+7*(min(a+i,min(b+j,c+k))));
        ans = max(ans, sqr(a+j)+sqr(b+k)+sqr(c+i)+7*(min(a+j,min(b+k,c+i))));
        ans = max(ans, sqr(a+k)+sqr(b+i)+sqr(c+j)+7*(min(a+k,min(b+i,c+j))));
      }
    }
    cout << ans << nl;
  }

  return 0;
}
