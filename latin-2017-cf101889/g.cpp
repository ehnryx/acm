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
vector<int> adj[N];
int bad[N];

ll dp[N][2][2];
ll solve(int cur, int real, int fake) {
  if (dp[cur][real][fake] == -1) {
    if (cur == 0) {
      dp[cur][real][fake] = (real == fake);
    }
    else if (bad[cur] == -1) {
      ll res = 0;
      for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
          for (int ii=0; ii<2; ii++) {
            for (int jj=0; jj<2; jj++) {
              if (real == !(i&j) && fake == !(ii&jj)) {
                res = (res + solve(adj[cur][0],i,ii) * solve(adj[cur][1],j,jj)) % MOD;
              }
            }
          }
        }
      }
      dp[cur][real][fake] = res;
    }
    else if (fake != bad[cur]) {
      dp[cur][real][fake] = 0;
    }
    else {
      ll res = 0;
      for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
          if (real == !(i&j)) {
            for (int ii=0; ii<2; ii++) {
              for (int jj=0; jj<2; jj++) {
                res = (res + solve(adj[cur][0],i,ii)*solve(adj[cur][1],j,jj)) % MOD;
              }
            }
          }
        }
      }
      dp[cur][real][fake] = res;
    }
  }
  return dp[cur][real][fake];
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

  int n, a, b, v;
  cin >> n;

  for (int i=1; i<=n; i++) {
    cin >> a >> b >> v;
    adj[i].push_back(a);
    adj[i].push_back(b);
    bad[i] = v;
  }

  cout << (solve(1,1,0) + solve(1,0,1)) % MOD << nl;

  return 0;
}
