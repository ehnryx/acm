#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3000+1;
const int L = 12;
int g[N][N];
int row[N][N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, a, b;
  cin >> n >> m >> a >> b;

  int x, y, z;
  cin >> g[0][0] >> x >> y >> z;
  For(i,n) {
    For(j,m) {
      if (j>0) {
        g[i][j] = ((ll)g[i][j-1]*x + y) % z;
      } else if (i>0) {
        g[i][j] = ((ll)g[i-1][m-1]*x + y) % z;
      }
    }
  }

  map<int,int> cur;

  For(i,n) {
    cur.clear();
    For(j,b) {
      cur[g[i][j]]++;
    }
    row[i][0] = cur.begin()->first;
    For(j,m-b) {
      cur[g[i][j+b]]++;
      if (--cur[g[i][j]] == 0) {
        cur.erase(g[i][j]);
      }
      row[i][j+1] = cur.begin()->first;
    }
  }

  ll ans = 0;
  FOR(j,0,m-b) {
    cur.clear();
    For(i,a) {
      cur[row[i][j]]++;
    }
    ans += cur.begin()->first;
    For(i,n-a) {
      cur[row[i+a][j]]++;
      if (--cur[row[i][j]] == 0) {
        cur.erase(row[i][j]);
      }
      ans += cur.begin()->first;
    }
  }
  cout << ans << nl;

  return 0;
}
