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
  for (int i=n-1; i>=0; i--) {
    cin >> a[i];
  }

  int lis[n], lds[n];
  memset(lis, INF, sizeof lis);
  memset(lds, INF, sizeof lds);

  int ans = 0;
  for (int i=0; i<n; i++) {
    int* inc = lower_bound(lis, lis+n, a[i]);
    int* dec = lower_bound(lds, lds+n, -a[i]);
    ans = max(ans, (int)(inc-lis + dec-lds + 1));
    *inc = a[i];
    *dec = -a[i];
  }
  cout << ans << nl;

  return 0;
}
