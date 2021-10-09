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
const ll MOD = 10056;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1e3+1;
ll ans[N];
ll ncr[N][N];

ll power(ll b, int e) {
  ll res = 1;
  for (; e>0; e/=2) {
    if (e&1) res = res*b % MOD;
    b = b*b % MOD;
  }
  return res;
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

  For(i,N) {
    ncr[i][0] = ncr[i][i] = 1;
    FOR(j,1,i-1) {
      ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % MOD;
    }
  }

  For(n,N) {
    FOR(k,0,n) {
      FOR(j,0,k) {
        if (j%2) ans[n] -= ncr[k][j] * power(k-j,n) % MOD;
        else ans[n] += ncr[k][j] * power(k-j,n) % MOD;
      }
    }
    ans[n] = (ans[n] % MOD + MOD) % MOD;
  }

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    cout << ans[n] << nl;
  }

  return 0;
}
