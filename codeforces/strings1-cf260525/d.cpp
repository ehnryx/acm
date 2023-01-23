#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string s;
  cin >> s;
  int n_pals;
  cin >> n_pals;
  const int n = size(s);

  vector cost(n, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<=i; j++) {
      int lmid = (i + j) / 2;
      int rmid = (i + j + 1) / 2;
      for(int k=0; lmid-k>=j; k++) {
        cost[j][i] += s[lmid-k] != s[rmid+k];
      }
    }
  }

  static constexpr int big = numeric_limits<int>::max();
  vector dp(n+1, vector<int>(n_pals+1, big));
  vector bt(n+1, vector<pair<int, int>>(n_pals+1));
  dp[0][0] = 0;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n_pals; j++) {
      for(int k=0; k<i; k++) {
        if(dp[k][j-1] == big) continue;
        if(int cur = dp[k][j-1] + cost[k][i-1]; cur < dp[i][j]) {
          dp[i][j] = cur;
          bt[i][j] = pair(k, j-1);
        }
      }
    }
  }

  auto ans = min_element(begin(dp.back()), end(dp.back()));
  cout << *ans << nl;

  vector<string> res;
  auto at = pair(n, (int)(ans - begin(dp.back())));
  while(at.first != 0) {
    auto nxt = bt[at.first][at.second];
    int lmid = (nxt.first + at.first - 1) / 2;
    int rmid = (nxt.first + at.first) / 2;
    for(int k=0; lmid-k>=nxt.first; k++) {
      if(s[lmid-k] != s[rmid+k]) {
        s[lmid-k] = s[rmid+k];
      }
    }
    res.emplace_back(s.begin() + nxt.first, s.begin() + at.first);
    at = nxt;
  }
  cout << res.back();
  for(auto it : res | views::reverse | views::drop(1)) {
    cout << "+" << it;
  }
  cout << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
