#include <bits/stdc++.h>
using namespace std;
#define FILENAME "easy"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

bool digit(char c) {
  return '0' <= c && c <= '9';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  string s; cin >> s;
  const int n = s.size();
  bool bad = false;
  for (int i = 0; i < n; i++) {
    if (s[i] == '-') {
      cout << s[i++];
      if (digit(s[i]))
        cout << s[i];
      bad = true;
      continue;
    }
    if (bad && digit(s[i])) {
      cout << '+';
    }
    if (s[i] == '+' || s[i] != '0')
      bad = false;
    cout << s[i];
  }
  cout << endl;

  return 0;
}

