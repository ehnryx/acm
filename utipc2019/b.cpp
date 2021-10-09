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
const ll MOD = 998244353;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e5+1;
int even[N], suff[N];
ll dp[N][2][2]; // idx, tot, suf

ll solve(const string& ss, bool eq) {
  memset(dp, 0, sizeof dp);
  memset(even, 0, sizeof even);
  memset(suff, 0, sizeof suff);
  int n = ss.size();

  for (int i=0; i<n; i++) {
    int d = ss[i]-'0';
    if (d%2 == 0) suff[i+1] = suff[i] ^ 1;
    else suff[i+1] = (i&1) ^ suff[i];
    even[i+1] = even[i] ^ suff[i+1];

    if (i == 0) {
      for (int j=1; j<d; j++) {
        if (j%2 == 0) {
          dp[i+1][1][1] = (dp[i+1][1][1] + 1) % MOD;
        } else {
          dp[i+1][0][0] = (dp[i+1][0][0] + 1) % MOD;
        }
      }
    }

    else {
      // init
      for (int j=1; j<10; j++) {
        if (j%2 == 0) {
          dp[i+1][1][1] = (dp[i+1][1][1] + 1) % MOD;
        } else {
          dp[i+1][0][0] = (dp[i+1][0][0] + 1) % MOD;
        }
      }

      // free
      for (int t=0; t<2; t++) {
        for (int s=0; s<2; s++) {
          // add even
          dp[i+1][t][s] = (dp[i+1][t][s] + 5*dp[i][t^s][s^1]) % MOD;
          // add odd
          dp[i+1][t][s] = (dp[i+1][t][s] + 5*dp[i][t^s][i^s]) % MOD;
        }
      }

      // follow
      for (int add=0; add<d; add++) {
        for (int t=0; t<2; t++) {
          for (int s=0; s<2; s++) {
            if (add%2 == 0) {
              dp[i+1][t][s] = (dp[i+1][t][s] + (even[i]==(t^s) && suff[i]==(s^1))) % MOD;
            } else {
              dp[i+1][t][s] = (dp[i+1][t][s] + (even[i]==(t^s) && suff[i]==(i^s))) % MOD;
            }
          }
        }
      }
    }
  }

  ll ans = (dp[n][1][0] + dp[n][1][1] + (even[n]==1 && eq)) % MOD;
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

  string l, r;
  cin >> l;
  cin >> r;
  cout << (solve(r,true) - solve(l,false) + MOD) % MOD << nl;

  return 0;
}
