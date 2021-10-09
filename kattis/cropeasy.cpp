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
  for (int tt=1; tt<=T; tt++) {
    cout << "Case #" << tt << ": ";
    int n, a, b, c, d, x, y, m;
    cin >> n >> a >> b >> c >> d >> x >> y >> m;
    vector<pt> p;
    for (int i=0; i<n; i++) {
      p.push_back(pt(x,y));
      x = ((ll)a*x+b)%m;
      y = ((ll)c*y+d)%m;
    }
    int ans = 0;
    for (int i=0; i<n; i++) {
      for (int j=0; j<i; j++) {
        for (int k=0; k<j; k++) {
          pt g = p[i]+p[j]+p[k];
          ans += (llround(g.real())%3==0 && llround(g.imag())%3==0);
        }
      }
    }
    cout << ans << nl;
  }

  return 0;
}
