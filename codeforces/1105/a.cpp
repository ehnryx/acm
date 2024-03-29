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

  int n;
  cin >> n;

  int a[n];
  for (int i=0; i<n; i++) {
    cin >> a[i];
  }

  int best = INF;
  int ans = -1;
  for (int t=1; t<=100; t++) {
    int cur = 0;
    for (int i=0; i<n; i++) {
      cur += min(abs(a[i]-t), min(abs(a[i]-t-1), abs(a[i]-t+1)));
    }
    if (cur < best) {
      best = cur;
      ans = t;
    }
  }
  assert(ans != -1);

  cout << ans << " " << best << nl;

  return 0;
}
