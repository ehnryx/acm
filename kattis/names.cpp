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

int solve(string s, int len) {
  int n = s.size();
  int extra = len-n;
  for (int i=extra-1; i>=0; i--) {
    s.push_back(s[i]);
  }
  string t = s;
  reverse(t.begin(), t.end());
  int diff = 0;
  for (int i=0; i<len; i++) {
    diff += (s[i]!=t[i]);
  }
  return (diff+1)/2 + extra;
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  string s;
  cin >> s;
  int n = s.size();

  int ans = INF;
  for (int i=n; i<=2*n; i++) {
    ans = min(ans, solve(s,i));
  }
  cout << ans << nl;

  return 0;
}
