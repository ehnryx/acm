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

  char t; string s;
  cin >> t >> s;
  if (t == 'E') {
    char p = 0;
    int cnt = 0;
    for (char c : s) {
      if (c != p) {
        if (cnt>0) cout << cnt;
        cout << c;
        cnt = 1;
        p = c;
      } else {
        cnt++;
      }
    }
    if (cnt>0) cout << cnt;
    cout << nl;
  }
  else {
    char p = 0;
    for (char c : s) {
      if (isdigit(c)) {
        for (int i=1; i<c-'0'; i++) {
          cout << p;
        }
      } else {
        p = c;
        cout << c;
      }
    }
    cout << nl;
  }

  return 0;
}
