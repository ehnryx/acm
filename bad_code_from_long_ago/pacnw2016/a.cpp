#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 5;
char s[N];
int dp[N];

int main() {
  scanf("%s", s + 1);
  int l = strlen(s + 1), ans = 0;
  for (int i = 1; i <= l; i++) {
    dp[i] = 1;
    for (int j = 1; j < i; j++) {
      if (s[j] < s[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    ans = max(ans, dp[i]);
  }
  printf("%d\n", 26 - ans);
  return 0;
}
