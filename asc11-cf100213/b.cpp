#include <bits/stdc++.h>
using namespace std;

#define FILENAME "brick"

const int N = 9;
long long dp[N][N];

int main() {
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  dp[1][1] = 1;
  dp[1][2] = 0;
  dp[1][3] = 1;
  dp[1][4] = 0;
  dp[1][5] = 1;
  dp[1][6] = 0;
  dp[1][7] = 1;
  dp[1][8] = 0;
  dp[2][1] = 1;
  dp[2][2] = 1;
  dp[2][3] = 4;
  dp[2][4] = 5;
  dp[2][5] = 12;
  dp[2][6] = 15;
  dp[2][7] = 30;
  dp[2][8] = 37;
  dp[3][1] = 1;
  dp[3][2] = 3;
  dp[3][3] = 13;
  dp[3][4] = 32;
  dp[3][5] = 97;
  dp[3][6] = 214;
  dp[3][7] = 549;
  dp[3][8] = 1144;
  dp[4][1] = 1;
  dp[4][2] = 7;
  dp[4][3] = 41;
  dp[4][4] = 162;
  dp[4][5] = 691;
  dp[4][6] = 2255;
  dp[4][7] = 8197;
  dp[4][8] = 24790;
  dp[5][1] = 1;
  dp[5][2] = 15;
  dp[5][3] = 125;
  dp[5][4] = 770;
  dp[5][5] = 4627;
  dp[5][6] = 21928;
  dp[5][7] = 111158;
  dp[5][8] = 478500;
  dp[6][1] = 1;
  dp[6][2] = 31;
  dp[6][3] = 374;
  dp[6][4] = 3537;
  dp[6][5] = 30191;
  dp[6][6] = 206521;
  dp[6][7] = 1466264;
  dp[6][8] = 8947384;
  dp[7][1] = 1;
  dp[7][2] = 63;
  dp[7][3] = 1105;
  dp[7][4] = 15897;
  dp[7][5] = 193255;
  dp[7][6] = 1897387;
  dp[7][7] = 18898328;
  dp[7][8] = 162815499;
  dp[8][1] = 1;
  dp[8][2] = 127;
  dp[8][3] = 3238;
  dp[8][4] = 70500;
  dp[8][5] = 1222265;
  dp[8][6] = 17168439;
  dp[8][7] = 240144512;
  dp[8][8] = 2914401494;

  int m, n;
  cin >> m >> n;
  cout << dp[m][n] << '\n';

  return 0;
}
