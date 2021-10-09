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

const int N = 1e3+1;
bool adj[N][N];
int colour[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, m, k, a, b;
  cin >> n >> m >> k;

  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    adj[a][b] = true;
    adj[b][a] = true;
  }

  int cur = 0;
  for (int i = 1; i <= n; i++) {
    if (!colour[i]) {
      colour[i] = ++cur;
    }
    for (int j = 1; j <= n; j++) {
      if (!adj[i][j]) colour[j] = colour[i];
    }
  }

  bool bad = false;
  if (cur > k) bad = true;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (adj[i][j] && colour[i] == colour[j]) bad = true;
      if (!adj[i][j] && colour[i] != colour[j]) bad = true;
    }
  }

  if (bad) {
    cout << -1 << nl;
  } else {
    for (int i = 1; i <= n; i++) {
      cout << colour[i] << " ";
    }
    cout << nl;
  }

  return 0;
}
