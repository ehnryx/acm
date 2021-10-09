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

  int cnt[n];
  for (int k=2; k<=n; k++) {
    if (n%k == 0) {
      memset(cnt, 0, k*sizeof(int));
      bool ok = true;
      for (int i=0; i<n; i++) {
        cnt[a[i]%k]++;
        if (cnt[a[i]%k]*k > n) {
          ok = false;
          break;
        }
      }
      if (ok) {
        cout << k << nl;
        return 0;
      }
    }
  }

  cout << -1 << nl;

  return 0;
}
