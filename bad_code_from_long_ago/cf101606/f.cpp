#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ld dp[401][401];
void init() {
  for (int i = 0; i <= 400; i++) {
    for (int j = 0; j <= 400; j++) {
      dp[i][j] = -1;
    }
  }
  for (int i = 0; i <= 400; i++) {
    dp[i][0] = 0;
  }
}

ld solve(int n, int k) {
  if (dp[n][k] != -1) {
    return dp[n][k];
  }
  if (n > 0) {
    return dp[n][k] = 0.5*solve(n, k-1) + 0.5*(solve(n-1, k-1) + 1);
  }
  else {
    return dp[n][k] = 0.5*solve(n, k-1) + 0.5*(solve(n+1, k-1) - 1);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  init();

  int n, k;
  cin >> n >> k;
  cout << solve(n, k) << nl;

  return 0;
}
