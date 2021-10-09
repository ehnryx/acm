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

const int N = 1e4+1;
const int K = 1e2+1;

vector<int> adj[N];
int x[N][K], y[N][K];
int k[N];

ll dp[N][K];
ll solve(int cur, int par, int point) {
  if (dp[cur][point] != -1) return dp[cur][point];

  ll res = 0;
  for (int i : adj[cur]) {
    if (i != par) {
      ll down = INFLL;
      for (int j=0; j<k[i]; j++) {
        int dx = abs(x[cur][point] - x[i][j]);
        int dy = abs(y[cur][point] - y[i][j]);
        down = min(down, solve(i, cur, j) + dx + dy);
      }
      assert(down != INFLL);
      res += down;
    }
  }
  return dp[cur][point] = res;
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

  memset(dp, -1, sizeof dp);

  int n, a, b;
  cin >> n;

  for (int i=1; i<n; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int i=1; i<=n; i++) {
    cin >> k[i];
    for (int j=0; j<k[i]; j++) {
      cin >> x[i][j] >> y[i][j];
    }
  }

  ll ans = INFLL;
  for (int j=0; j<k[1]; j++) {
    ans = min(ans, solve(1,0,j));
  }
  assert(ans != INFLL);
  cout << ans << nl;

  return 0;
}
