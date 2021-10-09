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

  vector<int> p[2][2]; // direction, type
  for (int i=0; i<n; i++) {
    int a, b; char c;
    cin >> a >> b >> c;
    p[0][c=='b'].push_back(a);
    p[1][c=='b'].push_back(b);
  }

  for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++) {
      sort(p[i][j].begin(), p[i][j].end());
    }
  }

  int ans = 0;
  for (int i=0; i<2; i++) {
    for (int j=0; j<2; j++) {
      ans = max(ans, (int)p[i][j^1].size());
      for (int k=0; k<p[i][j].size(); k++) {
        int other = p[i][j^1].end() - lower_bound(p[i][j^1].begin(), p[i][j^1].end(), p[i][j][k]);
        ans = max(ans, k+1 + other);
      }
    }
  }

  cout << ans << nl;

  return 0;
}
