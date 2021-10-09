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

  int a, b;
  cin >> a >> b;
  int a1, b1;
  cin >> a1 >> b1;
  int a2, b2;
  cin >> a2 >> b2;

  if (a1+a2<=a && max(b1,b2)<=b) cout << "YES" << nl;
  else if (a1+b2<=a && max(b1,a2)<=b) cout << "YES" << nl;
  else if (b1+a2<=a && max(a1,b2)<=b) cout << "YES" << nl;
  else if (b1+b2<=a && max(a1,a2)<=b) cout << "YES" << nl;
  else if (a1+a2<=b && max(b1,b2)<=a) cout << "YES" << nl;
  else if (a1+b2<=b && max(b1,a2)<=a) cout << "YES" << nl;
  else if (b1+a2<=b && max(a1,b2)<=a) cout << "YES" << nl;
  else if (b1+b2<=b && max(a1,a2)<=a) cout << "YES" << nl;
  else cout << "NO" << nl;

  return 0;
}
