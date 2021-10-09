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
const int MAXN = 5005;

int N, C;
pair<int, int> dp[MAXN][MAXN];
vector<pair<int, int>> b;


int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);
  
  cin >> N >> C;
  b.resize(N+1);
  for (int i = 1; i <= N; i++)
    cin >> b[i].first >> b[i].second;
  b[0] = {INF, INF};
  memset(dp, INF, sizeof dp);
  for (int i = 0; i <= C+1; i++)
    dp[0][i] = {0, 0};
  for (int i = 1; i <= N; i++) {
    pair<int, int> bpair = {INF, INF};
    for (int j = b[i].second; j <= C; j++) {
      dp[i][j] = min(make_pair(dp[i-1][C+1].first + b[i].second, b[i].second),
          make_pair(dp[i-1][j-b[i].first].first - dp[i-1][j-b[i].first].second + max(dp[i-1][j-b[i].first].second, b[i].second), max(dp[i-1][j-b[i].first].second, b[i].second)));
      if (dp[i][j].first < bpair.first)
        bpair = dp[i][j];
    }
    dp[i][C+1] = bpair;
  }
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= C+1; j++)
      cout << dp[i][j].first << "," << dp[i][j].second << " ";
    cout << endl;
  }
  cout << dp[N][C+1].first << endl;
      

  return 0;
}
