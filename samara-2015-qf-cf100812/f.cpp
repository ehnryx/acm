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

  int n, m;
  cin >> n >> m;

  int h[n][m], v[n][m];
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      h[i][j] = s[j] == '.';
      v[i][j] = s[j] == '.';
    }
  }

  int ans[1+max(n,m)];
  memset(ans, 0, sizeof ans);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i > 0 && v[i][j]) v[i][j] += v[i-1][j];
      if (j > 0 && h[i][j]) h[i][j] += h[i][j-1];
      ans[v[i][j]]++;
      ans[h[i][j]]++;
    }
  }

  for (int i = max(n,m); i > 1; i--) {
    ans[i-1] += ans[i];
  }

  cout << ans[1] / 2 << " ";
  for (int i = 2; i <= max(n,m); i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
