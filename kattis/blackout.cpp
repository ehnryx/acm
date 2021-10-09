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

bool move(int a, int b, int x, int y) {
  cout << min(a,x) << " " << min(b,y) << " " << max(a,x) << " " << max(b,y) << endl;
  string s;
  cin >> s;
  return s == "MOVE";
}

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
    int a, b, x, y;
    tie(a,b,x,y) = make_tuple(3,1,3,6);
    while (move(a,b,x,y)) {
      cin >> a >> b >> x >> y;
      tie(a,b,x,y) = make_tuple(6-a,7-b,6-x,7-y);
    }
  }

  return 0;
}
