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
vector<int> adj[N];
int dur[N], cost[N];
int dp[N][N]; // time, ride

void init() {
  memset(dp, INF, sizeof dp);
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
  init();

  int x;
  cin >> x;

  int n, m, t, a, b;
  cin >> n >> m >> t;

  for (int i = 0; i < m; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for (int i = 1; i <= n; i++) {
    cin >> dur[i] >> cost[i];
  }

  dp[dur[1]][1] = cost[1]; // must use first ride
  for (int i = dur[1]; i < N; i++) {
    for (int j = 1; j <= n; j++) {
      // take ride again
      if (i+dur[j] < N) {
        dp[i+dur[j]][j] = min(dp[i+dur[j]][j], dp[i][j] + cost[j]);
      }

      // move on
      for (int v : adj[j]) {
        if (i+t+dur[v] < N) {
          dp[i+t+dur[v]][v] = min(dp[i+t+dur[v]][v], dp[i][j] + cost[v]);
        }
      }
    }
  }

  assert(dp[x][1] <= INF);
  if (dp[x][1] == INF) {
    cout << "It is a trap." << nl;
  } else {
    cout << dp[x][1] << nl;
  }

  return 0;
}
