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

  string s, t;
  cin >> s;
  cin >> t;

  reverse(s.begin(), s.end());
  reverse(t.begin(), t.end());

  int cnts, cntt;
  cnts = cntt = 0;
  for (int i=0; i<min(s.size(),t.size()); i++) {
    if (s[i]<t[i]) {
      s[i] = 0;
      cnts++;
    }
    else if (t[i]<s[i]) {
      t[i] = 0;
      cntt++;
    }
  }

  if (cnts==s.size()) {
    cout << "YODA" << nl;
  } else {
    reverse(s.begin(), s.end());
    int ans = 0;
    for (char c : s) {
      if (c>0) {
        ans = ans*10 + c-'0';
      }
    }
    cout << ans << nl;
  }

  if (cntt==t.size()) {
    cout << "YODA" << nl;
  } else {
    reverse(t.begin(), t.end());
    int ans = 0;
    for (char c : t) {
      if (c>0) {
        ans = ans*10 + c-'0';
      }
    }
    cout << ans << nl;
  }

  return 0;
}
