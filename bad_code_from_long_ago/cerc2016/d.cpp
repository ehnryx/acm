#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define nl '\n'

ll choose[51][51];
ld dp[11][11][11];

void init() {
  // init choose
  memset(choose, 0, sizeof(choose));
  for (int i = 0; i <= 50; i++) {
    choose[i][0] = choose[i][i] = 1;
    for (int j = 1; j < i; j++) {
      choose[i][j] = choose[i-1][j-1] + choose[i-1][j];
    }
  }
  // init dp
  for (int i = 0; i <= 10; i++)
    for (int j = 0; j <= 10; j++)
      for (int k = 0; k <= 10; k++)
        dp[i][j][k] = -1;
}

ld find_expected(const int n, const int d, int a, int b, int c) {
  if (a+b == 0 || b+c == 0) {
    return 0;
  }
  if (dp[a][b][c] == -1) {
    ld p;
    dp[a][b][c] = 1;
    for (int i = 0; i <= a; i++) {
      for (int j = 0; j <= b; j++) {
        for (int k = 0; k <= c; k++) {
          if (i+j+k > 0 && i+j+k <= d) {
            p = (ld) choose[a][i]*choose[b][j]*choose[c][k]*choose[n-a-b-c][d-i-j-k] / choose[n][d];
            dp[a][b][c] += p * find_expected(n, d, a-i, b-j, c-k);
          }
        }
      }
    }
    p = (ld) choose[n-a-b-c][d]/choose[n][d];
    dp[a][b][c] /= (1-p);
  }
  return dp[a][b][c];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(5);

  init();

  int n, d, c;
  cin >> n >> d >> c;

  int temp;
  set<int> seen;
  for (int i = 0; i < c; i++) {
    cin >> temp;
    seen.insert(temp);
  }
  int overlap = 0;
  for (int i = 0; i < c; i++) {
    cin >> temp;
    if (seen.count(temp)) {
      overlap++;
    }
  }

  cout << find_expected(n, d, c-overlap, overlap, c-overlap) << nl;

  return 0;
}
