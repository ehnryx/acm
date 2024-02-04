#define MULTI_TEST
%:include "main.h"
SOLVE() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<int> think(26);
  for(char c : s) {
    think[c - 'A'] += 1;
  }
  int ans = 0;
  for(int i=0; i<26; i++) {
    ans += (think[i] >= i + 1);
  }
  cout << ans << nl;
}
