#include <bits/stdc++.h>

using namespace std;

const int N = 70 + 5;

char s[N];
unsigned long long dp[N][10][2];

void init(int n) {
  // dp[i][j][0..1] := i digits, last digit j, if started falling
  // dp[i][j][0] = dp[i - 1][k][0] (k <= j)
  // dp[i][j][1] = dp[i - 1][k][1] (k >= j)
  //             + dp[i - 1][k][0] (k > j)
  for (int i = 0; i < 10; i++) {
    dp[1][i][0] = 1;
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < 10; j++) {
      // dp[i][j][0]
      for (int k = 0; k <= j; k++) {
        dp[i][j][0] += dp[i - 1][k][0];
      }
      // dp[i][j][1]
      dp[i][j][1] += dp[i - 1][j][1];
      for (int k = j + 1; k < 10; k++) {
        dp[i][j][1] += dp[i - 1][k][0] + dp[i - 1][k][1];
      }
    }
  }
}

bool hill_number(char s[]) {
  int l = strlen(s);
  bool started_falling = false;
  for (int i = 1; i < l; i++) {
    if (!started_falling) {
      if (s[i] < s[i - 1]) {
        started_falling = true;
      }
    } else {
      if (s[i] > s[i - 1]) {
        return false;
      }
    }
  }
  return true;
}

unsigned long long compute(char s[]) {
  int l = strlen(s);
  unsigned long long ans = 0;
  for (int i = 1; i < l; i++) {
    for (int j = 1; j < 10; j++) {
      ans += dp[i][j][0] + dp[i][j][1];
    }
  }
  for (int i = 1; i < s[0] - '0'; i++) {
    ans += dp[l][i][0] + dp[l][i][1];
  }
  bool started_falling = false;
  for (int i = 1; i < l; i++) {
    if (!started_falling) {
      for (int j = s[i - 1] - '0'; j < s[i] - '0'; j++) {
        ans += dp[l - i][j][1];
        /*
        if (l - i == 1 && j > s[i - 1] - '0') {
          ans += dp[l - i][j][0];
        }
        */
      }
      for (int j = 0; j < s[i] - '0'; j++) { // equal holds?
        ans += dp[l - i][j][0];
      }
      if (s[i] < s[i - 1]) {
        started_falling = true;
      }
    } else {
      for (int j = 0; j < s[i] - '0' && j <= s[i - 1] - '0'; j++) {
        ans += dp[l - i][j][0];
      }
    }
  }
  return ans;
}

int main() {
  init(70);
  /*
  for (int i = 1; i <= 3; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < 2; k++) {
        printf("dp[%d][%d][%d] = %llu\n", i, j, k, dp[i][j][k]);
      }
    }
  }
  */
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    if (!hill_number(s)) {
      puts("-1");
      continue;
    }
    cout << compute(s) + 1 << endl;
  }
  return 0;
}
