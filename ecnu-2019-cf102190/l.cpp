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

int v[7];

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
    FOR(i,1,6) {
      cin >> v[i];
    }

    // 6 and 5
    int ans = v[6] + v[5];
    v[1] -= min(v[1], v[5]);

    // 4
    ans += v[4];
    int m42 = min(v[4], v[2]);
    v[2] -= m42; v[4] -= m42;
    int m41 = min(v[4], (v[1]+1)/2);
    v[1] -= min(v[1], 2*m41);

    // 3
    ans += v[3]/2;
    v[3] %= 2;
    ans += v[3];
    if (v[3] > 0) {
      if (v[2] > 0) {
        v[2]--;
        v[1] -= min(v[1], 1);
      } else {
        v[1] -= min(v[1], 3);
      }
    }

    // 2
    ans += v[2]/3;
    v[2] %= 3;
    ans += (v[2]>0);
    if (v[2] == 1) {
      v[1] -= min(v[1], 4);
    } else if (v[2] == 2) {
      v[1] -= min(v[1], 2);
    }

    // 1
    ans += v[1]/6;
    v[1] %= 6;
    ans += (v[1]>0);

    // 0
    cout << ans << nl;
  }

  return 0;
}
