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



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while (T--) {
    int x, n;
    cin >> x >> n;

    if (n > x) {
      cout << -1 << nl;
    }
    else {
      int a = x/n;
      int extra = x - a*n;
      for (int i = 0; i < n-extra; i++) {
        cout << a << " ";
      }
      for (int i = 0; i < extra; i++) {
        cout << a+1 << " ";
      }
      cout << nl;
    }
  }

  return 0;
}
