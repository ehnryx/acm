#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

int dp[24][2][2];
int solve(string s, int i, int out, int in) {
  if (dp[i][out][in] != -1) {
    return dp[i][out][in];
  }
  int res = INF;
  int len = s.size();
  if (i == len/2) {
    if (len%2 == 0) {
      if (out == in) {
        res = 0;
      } else {
        res = INF;
      }
    } else {
      if (out) {
        res = 10-(s[i]-'0')-in;
      } else if (s[i] == '9' && in) {
        res = INF;
      } else {
        res = 0;
      }
    }
  } else {
    if (out) {
      for (int d = 0; d < s[i]-'0'; d++) {
        int left = 10+d - (s[i]-'0');
        int right = d - (s[len-1-i]-'0');
        if (d < s[len-1-i]-'0'+in) {
          right += 10;
          res = min(res, left + right-in + solve(s, i+1, 0, 1));
          if (left > 0)
            res = min(res, left-1 + right-in + solve(s, i+1, 1, 1));
        } else {
          res = min(res, left + right-in + solve(s, i+1, 0, 0));
          if (left > 0)
            res = min(res, left-1 + right-in + solve(s, i+1, 1, 0));
        }
      }
    }
    else {
      for (int d = s[i]-'0'; d < 10; d++) {
        int left = d - (s[i]-'0');
        int right = d - (s[len-1-i]-'0');
        if (d < s[len-1-i]-'0'+in) {
          right += 10;
          res = min(res, left + right-in + solve(s, i+1, 0, 1));
          if (left > 0)
            res = min(res, left-1 + right-in + solve(s, i+1, 1, 1));
        } else {
          res = min(res, left + right-in + solve(s, i+1, 0, 0));
          if (left > 0)
            res = min(res, left-1 + right-in + solve(s, i+1, 1, 0));
        }
      }
    }
  }
  return dp[i][out][in] = res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  memset(dp, -1, sizeof(dp));
  string s;
  cin >> s;
  int ans = min(solve(s, 0, 0, 0), solve(s, 0, 1, 0));
  cout << ans << nl;

  return 0;
}
