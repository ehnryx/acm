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
ll dp[N];
ll cnt[N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;

  int a;
  for (int i = 0; i < n; i++) {
    cin >> a;
    cnt[a]++;
  }

  dp[0] = 0;
  dp[1] = cnt[1];
  for (int i = 2; i < N; i++) {
    dp[i] = max(dp[i-1], dp[i-2] + i*cnt[i]);
  }

  cout << dp[N-1] << nl;

  return 0;
}
