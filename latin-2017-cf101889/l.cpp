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

const int N = 1e5+1;
set<int> ones[2];
int dist[2][N];
int pref[2][N];

int solve(int s, int t, int d, int $) {
  if (s > t) swap(s, t);
  if ((t-s)%2 != d%2) d--;

  int extra = d - (t-s);
  int cur = pref[$][t-1] - pref[$][s-1];
  int ans = cur + extra*5;

  //cerr << "extra " << extra << nl;

  if (extra > 0) {
    auto it = ones[$].lower_bound(s);
    if (it != ones[$].end() && *it < t) {
      ans = min(ans, cur + extra);
    } else {
      if (it != ones[$].end() && 2*(*it-t) <= extra) {
        ans = min(ans, cur + 2*(pref[$][*it-1] - pref[$][t-1]) + extra - 2*(*it-t));
      }
      if (it != ones[$].begin() && 2*(s-*prev(it)) <= extra) {
        --it;
        ans = min(ans, cur + 2*(pref[$][s-1] - pref[$][*it-1]) + extra - 2*(s-*it));
      }
    }
  }

  //cerr << "$: " << $ << " -> " << ans << " " << pref[$][t-1] - pref[$][s-1] << nl;
  return ans;
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

  int n;
  cin >> n;

  pref[0][0] = pref[1][0] = 0;
  for (int t=0; t<2; t++) {
    for (int i=1; i<n; i++) {
      cin >> dist[t][i];
      pref[t][i] = pref[t][i-1] + dist[t][i];
      if (dist[t][i] == 1) {
        ones[t].insert(i);
      }
    }
  }

  int q, x1, y1, x2, y2;
  cin >> q;
  while (q--) {
    cin >> x1 >> y1 >> x2 >> y2;
    int diff = max(abs(x1-x2), abs(y1-y2));
    cout << solve(x1, x2, diff, 0) + solve(y1, y2, diff, 1) << nl;
  }

  return 0;
}
