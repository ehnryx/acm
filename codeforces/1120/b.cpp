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

const int C = 1e5;


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

  char s[n+1], t[n+1];
  cin >> s;
  cin >> t;

  int ans = 0;
  vector<pii> moves;
  for (int i=1; i<n; i++) {
    if (s[i-1] != t[i-1]) {
      ans += abs(s[i-1]-t[i-1]);
      while (s[i-1] < t[i-1]) {
        if (moves.size() < C) moves.push_back({i,1});
        s[i-1]++;
        s[i]++;
      }
      while (s[i-1] > t[i-1]) {
        if (moves.size() < C) moves.push_back({i,-1});
        s[i-1]--;
        s[i]--;
      }
    }
  }

  if (s[n-1] != t[n-1]) {
    cout << -1 << nl;
  } else {
    for (int i=0; i<n; i++) {
      if (s[i]<'0' || s[i]>'9') {
        cout << -1 << nl;
        return 0;
      }
    }
    cout << ans << nl;
    for (const pii& it : moves) {
      cout << it.first << " " << it.second << nl;
    }
  }

  return 0;
}
