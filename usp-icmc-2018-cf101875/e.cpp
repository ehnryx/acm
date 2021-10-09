#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N = 450+2;
int dp[N][N];

int cost(int l, int r) {
  int n = r-l;
  return n*(n-1)/2;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, K;
  cin >> n >> K;

  string s;
  cin >> s;
  s = "0"+s+"0";

  memset(dp, INF, sizeof dp);
  dp[0][0] = 0;
  for (int i=1; i<=n+1; i++) {
    for (int j=0; j<i; j++) {
      int c = cost(j,i);
      for (int k=0; k<=n; k++) {
        if (s[i] == '0') dp[i][k] = min(dp[i][k], dp[j][k] + c);
        else if (k>0) dp[i][k] = min(dp[i][k], dp[j][k-1] + c);
      }
    }
  }

  for (int r=0; r<=n; r++) {
    if (dp[n+1][r] <= K) {
      cout << r << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
