#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  // dp
  int ans[51][1001];
  memset(ans, INF, sizeof(ans));
  for (int j = 1; j <= 1000; j++) {
    ans[1][j] = j;
  }
  for (int i = 2; i <= 50; i++) {
    ans[i][1] = 1;
    for (int j = 2; j <= 1000; j++) {
      ans[i][j] = ans[i-1][j];
      for (int k = 1; k <= j; k++) {
        ans[i][j] = min(ans[i][j], 1+max(ans[i-1][j-k], ans[i][k-1]));
      }
    }
  }
  cerr << "done" << nl;

  int id, balls, height;
  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cin >> id >> balls >> height;
    cout << cc << " " << ans[balls][height] << nl;
  }

  return 0;
}
