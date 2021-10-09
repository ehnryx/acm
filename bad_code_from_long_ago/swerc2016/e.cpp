#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000003;
const int L = 20 + 5, N = 26 + 26 + 10 + 5;

int dp[L][N][2][2][2];
set<string> blacklist;

string makestr(char a, char b = '\000') {
  char s[3];
  s[0] = a;
  s[1] = b;
  s[2] = '\000';
  return string(s);
}

bool is_lowercase(char c) {
  return c >= 'a' && c <= 'z';
}

bool is_uppercase(char c) {
  return c >= 'A' && c <= 'Z';
}

bool is_digit(char c) {
  return c >= '0' && c <= '9';
}

bool is_letter(char c) {
  return is_uppercase(c) || is_lowercase(c);
}

bool is_special(char c) {
  if (is_uppercase(c)) {
    c = c - 'A' + 'a';
  }
  return c == 'o' || c == 'i' || c == 'e' || c == 's' || c == 't' || (is_digit(c) && (c - '0') % 2);
}

string unify(string s) {
  string ans;
  for (char c : s) {
    char x = c;
    if (is_uppercase(x)) {
      x = x - 'A' + 'a';
    }
    switch (x) {
      case 'o': x = '0';
      case 'i': x = '1';
      case 'e': x = '3';
      case 's': x = '5';
      case 't': x = '7';
    }
    ans += x;
  }
  return ans;
}

bool safe(string s) {
  return blacklist.find(unify(s)) == blacklist.end();
}

int count(string s) {
  /*
  int ans = 1;
  for (char c : s) {
    if (is_letter(c)) {
      (ans *= is_special(c) ? 3 : 2) %= MOD;
    } else {
      (ans *= is_special(c) ? 2 : 1) %= MOD;
    }
  }
  return ans;
  */
  return 1;
}

int unsafe_ends_with(string s) {
  int ans = 0;
  for (auto b : blacklist) {
    if (b.length() < 2) {
      continue;
    }
    if (b.substr(b.length() - 2) == s) {
      (ans += count(b.substr(0, b.length() - 2))) %= MOD;
    }
  }
  return ans;
}

void debug(int a, int c) {
  for (int i = 0; i <= a; i++) {
    for (int j = 0; j < c; j++) {
      int ans = 0;
      for (int p = 0; p < 2; p++) {
        for (int q = 0; q < 2; q++) {
          for (int r = 0; r < 2; r++) {
            ans += dp[i][j][p][q][r];
          }
        }
      }
      printf("%d%c", ans, " \n"[j + 1 == c]);
    }
  }
}

int main() {
  int a, b, n;
  cin >> a >> b >> n;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    blacklist.insert(unify(s));
  }
  // dp[i][j][2][2][2] := # of safe passwords w/ length i, last char j, lowercase used?, uppercase used?, digit used?
  vector<char> cs;
  /*
  for (char i = 'a'; i <= 'z'; i++) {
    cs.push_back(i);
  }
  for (char i = 'A'; i <= 'Z'; i++) {
    cs.push_back(i);
  }
  for (char i = '0'; i <= '9'; i++) {
    cs.push_back(i);
  }*/
  for (char i = 'a'; i <= 'd'; i++) {
    cs.push_back(i);
  }
  puts("blacklist:");
  for (auto s : blacklist) {
    cout << s << endl;
  }
  int c = cs.size();
  for (int i = 0; i < c; i++) {
    if (safe(makestr(cs[i]))) {
      int lc = is_lowercase(cs[i]);
      int uc = is_uppercase(cs[i]);
      int dc = is_digit(cs[i]);
      dp[1][i][lc][uc][dc] = 1;
    }
  }
  for (int i = 2; i <= b; i++) {
    for (int j = 0; j < c; j++) {
      if (safe(makestr(cs[j]))) {
        for (int k = 0; k < c; k++) {
          string suffix = makestr(cs[k], cs[j]);
          cout << "suffix: " << suffix << endl;
          if (safe(suffix)) {
            for (int lc = 0; lc < 2; lc++) {
              for (int uc = 0; uc < 2; uc++) {
                for (int dc = 0; dc < 2; dc++) {
                  int lc_ = lc | is_lowercase(cs[j]);
                  int uc_ = uc | is_uppercase(cs[j]);
                  int dc_ = dc | is_digit(cs[j]);
                  (dp[i][j][lc_][uc_][dc_] += dp[i - 1][k][lc][uc][dc]) %= MOD;
                  (dp[i][j][lc_][uc_][dc_] += MOD - unsafe_ends_with(suffix)) %= MOD;
                  cout << dp[i][j][lc_][uc_][dc_] << endl;
                }
              }
            }
          }
        }
      }
    }
  }
  int ans = 0;
  for (int i = a; i <= b; i++) {
    for (int j = 0; j < c; j++) {
      (ans += dp[i][j][1][1][1]) %= MOD;
    }
  }
  printf("%d\n", ans);
  debug(b, c);
  return 0;
}
