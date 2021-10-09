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

const int N = 5e3+1;
bool hit[N][N];
pii pre[N][N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int tot, n;
  cin >> tot >> n;

  hit[0][0] = true;
  int val[n+1];
  for (int i=1; i<=n; i++) {
    cin >> val[i];
    for (int j=val[i]; j<=tot; j++) {
      if (hit[i-1][j-val[i]]) {
        hit[i][j] = true;
        pre[i][j] = pii(i-1,j-val[i]);
      } else if (hit[i-1][j]) {
        hit[i][j] = true;
        pre[i][j] = pii(i-1,j);
      }
    }
  }

  set<int> take;
  for (int i=tot; i>=0; i--) {
    if (hit[n][i]) {
      for (pii cur = pii(n,i); cur.first != 0; cur = pre[cur.first][cur.second]) {
        if (pre[cur.first][cur.second].second == cur.second) {
          take.insert(cur.first);
        }
      }
      break;
    }
  }

  int one = 0;
  int two = 0;
  for (int i=1; i<=n; i++) {
    if (take.count(i)) {
      cout << one << " ";
      one += val[i];
    } else {
      cout << two << " ";
      two += val[i];
    }
  }
  cout << nl;

  return 0;
}
