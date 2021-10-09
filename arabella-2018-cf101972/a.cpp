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

int sgn(int n) { return n<0 ? -1 : n>0 ? 1 : 0; }

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
    int a, b;
    cin >> a >> b;
    vector<pii> ans;
    bool s = false;
    if (sgn(a)==sgn(b)) {
      a = abs(a); b = abs(b);
    } else {
      a = abs(a); b = abs(b);
      s = true;
    }
    for (int n=a,p=1; n>0; n/=10,p*=10) {
      if (n%10==0) continue;
      for (int m=b,q=1; m>0; m/=10,q*=10) {
        if (m%10==0) continue;
        ans.push_back(pii(n%10 * p, m%10 * q));
      }
    }
    if (s) cout << "-";
    cout << ans[0].first << " x " << ans[0].second;
    for (int i=1; i<ans.size(); i++) {
      if (s) cout << " - ";
      else cout << " + ";
      cout << ans[i].first << " x " << ans[i].second;
    }
    cout << nl;
  }

  return 0;
}
