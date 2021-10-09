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

  int n, k, r;
  cin >> n >> k >> r;

  vector<bool> a(n+2);
  for (int i=0; i<k; i++) {
    int v;
    cin >> v;
    a[v] = true;
  }

  int cur = 0;
  for (int i=1; i<=r; i++) {
    cur += a[i];
  }
  int ans = 0;
  for (int i=r; i<=n; i++) {
    if (cur < 2) {
      ans++;
      cur++;
      if (a[i]) a[i-1] = true;
      else a[i] = true;
    }
    if (cur < 2) {
      ans++;
      cur++;
      if (a[i]) a[i-1] = true;
      else a[i] = true;
    }
    cur += a[i+1];
    cur -= a[i-r+1];
  }
  cout << ans << nl;

  return 0;
}
