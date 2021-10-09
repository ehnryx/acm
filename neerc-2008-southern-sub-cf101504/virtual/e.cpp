#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const int N = 1010;

const string mov = "LURDN";
const map<char, int> m = {
  {'L', 0},
  {'U', 1},
  {'R', 2},
  {'D', 3},
  {'N', 4}
};
const tuple<int, int> BAD = {m.at('R'), m.at('L')};

int n;
string s;
int dp[N][4][4][4];
string best[N][4][4][4];
int lval[N][4][4][4];

inline void update(int& x, string& b, int& lv, int val, int l, int r, int last) {
  if (x > val) {
    x = val;
    b.clear();
    b.push_back(mov[l]);
    b.push_back(mov[r]);
    lv = last;
  }
}

int solve(int pos, int l, int r, int last) {
  if (tie(l, r) == BAD) return INF;
  if (l == r) return INF;
  if (pos >= n) return 0;
  if (dp[pos][l][r][last] != -1) return dp[pos][l][r][last];
  int& ans = dp[pos][l][r][last];
  string& b = best[pos][l][r][last];
  int& lv = lval[pos][l][r][last];
  ans = INF;
  if (s[pos] == 'N') {
    update(ans, b, lv, solve(pos+1, l, r, 0), l, r, 0);
    // mov left
    for (int i = 0; i < 4; i++) {
      int cost = last & 1 ? 9 : 3;
      update(ans, b, lv, solve(pos+1, i, r, 1) + cost, i, r, 1);
    }
    // mov right
    for (int i = 0; i < 4; i++) {
      int cost = last & 2 ? 9 : 3;
      update(ans, b, lv, solve(pos+1, l, i, 2) + cost, l, i, 2);
    }
    // mov both
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        update(ans, b, lv, solve(pos+1, i, j, 3) + 10, i, j, 3);
      }
    }
  } else {
    if (l == m.at(s[pos])) {
      update(ans, b, lv, solve(pos+1, l, r, 1) + 1, l, r, 1);
    }
    if (r == m.at(s[pos])) {
      update(ans, b, lv, solve(pos+1, l, r, 2) + 1, l, r, 2);
    }
    // mov left
    int cost = last & 1 ? 9 : 3;
    update(ans, b, lv, solve(pos+1, m.at(s[pos]), r, 1) + cost, m.at(s[pos]), r, 1);
    // mov right
    cost = last & 2 ? 9 : 3;
    update(ans, b, lv, solve(pos+1, l, m.at(s[pos]), 2) + cost, l, m.at(s[pos]), 2);
    // mov both
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (i != m.at(s[pos]) && j != m.at(s[pos])) continue;
        update(ans, b, lv, solve(pos+1, i, j, 3) + 10, i, j, 3);
      }
    }
  }
  return dp[pos][l][r][last] = ans;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> s;
  memset(dp, -1, sizeof dp);
  cout << solve(0, m.at('L'), m.at('R'), 0) << nl;
  string cur = "LR"; int last = 0;
  for (int i = 0; i < n; i++) {
    string nex = best[i][m.at(cur[0])][m.at(cur[1])][last];
    last = lval[i][m.at(cur[0])][m.at(cur[1])][last];
    cur = nex;
    cout << cur << nl;
  }

  return 0;
}
