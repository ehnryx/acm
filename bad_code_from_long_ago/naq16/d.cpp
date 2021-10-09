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
const int MAXN = 5000;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  char s[MAXN+1];
  scanf("%s", s);
  int len = strlen(s);

  int value[MAXN+1];
  int maxq[MAXN+1][MAXN+1];
  int minq[MAXN+1][MAXN+1];
  memset(maxq, 0, sizeof(maxq));
  memset(minq, INF, sizeof(minq));
  value[0] = 0;
  for (int i = 0; i < len; i++) {
    if (s[i] == '(') value[i+1] = value[i]+1;
    else value[i+1] = value[i]-1;
  }
  for (int i = 0; i <= len; i++) {
    maxq[i][i] = value[i];
    minq[i][i] = value[i];
    for (int j = i+1; j <= len; j++) {
      maxq[i][j] = max(maxq[i][j-1], value[j]);
      minq[i][j] = min(minq[i][j-1], value[j]);
    }
  }

  for (int i = 0; i <= len; i++) {
    for (int j = i; j <= len; j++) {
      int shift = 2*(value[i] - value[j]);
      if (minq[0][i] >= 0 && 2*value[i] - maxq[i][j] >= 0 
          && shift + minq[j][len] >= 0 
          && shift + value[len] == 0) {
        cout << "possible" << endl;
        return 0;
      }
    }
  }
  cout << "impossible" << endl;

  return 0;
}
