#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;

  const int M = 10;
  vector cnt(M, vector<int>(M));
  cnt[0][s[0] - '0'] = 1;
  for (int i = 1; i < s.size(); i++) {
    if (s[i - 1] != s[i]) {
      cnt[s[i - 1] - '0'][s[i] - '0'] += 1;
    }
  }

  vector<int> order(M);
  iota(begin(order), end(order), 0);
  int ans = numeric_limits<int>::max();
  do {
    vector<int> pos(M);
    for (int i = 0; i < M; i++) {
      pos[order[i]] = i;
    }
    int res = s.size();
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        res += cnt[i][j] * abs(pos[i] - pos[j]);
      }
    }
    ans = min(ans, res - 1);
  } while (next_permutation(begin(order) + 1, end(order)));
  cout << ans << nl;

  return 0;
}
