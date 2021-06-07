#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
using ll = long long;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  vector<vector<int>> g;
  for (string s; getline(cin, s); ) {
    istringstream in(s);
    vector<int> row;
    for (int v; in >> v; ) {
      row.push_back(v);
    }
    g.push_back(move(row));
  }

  int n = size(g);
  vector dp(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      dp[i][j] = g[i - 1][j - 1] + max(dp[i - 1][j - 1], dp[i - 1][j]);
    }
  }
  cout << *max_element(begin(dp.back()), end(dp.back())) << nl;

  return 0;
}
