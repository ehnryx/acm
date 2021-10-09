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

const int N = 2e5+1;
vector<int> adj[N];
int dp[N][3];

void init() {
  memset(dp, -1, sizeof dp);
}

int solve(int cur, int par, int val) {
  if (dp[cur][val] != -1) return dp[cur][val];

  bool child = false;
  int take = 1;
  int leave = 0;
  int mindiff = INF;
  for (int x : adj[cur]) {
    if (x != par) {
      child = true;
      take += solve(x, cur, 2);
      if (val != 0) {
        leave += solve(x, cur, 1);
        mindiff = min(mindiff, solve(x, cur, 0) - solve(x, cur, 1));
      }
    }
  }

  if (val == 1) {
    if (!child) return dp[cur][val] = 1;
    else return dp[cur][val] = leave + mindiff;
  } else {
    if (val != 0) {
      take = min(take, leave);
    }
    return dp[cur][val] = take;
  }
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

  int n;
  cin >> n;

  int a, b;
  for (int i = 1; i < n; i++) {
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int ans = 0;
  for (int i : adj[1]) {
    ans += solve(i, 1, 0) - 1;
  }
  cout << ans << nl;

  return 0;
}
