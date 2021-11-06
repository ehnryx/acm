#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"
//#include "../../../lca/data_structure/splay_tree.h"
#include "../../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n+1);
    vector<Int> dp(1, 0);
    vector<int> div(1, 1);
    Int ans = 0;
    for(int i=1; i<=n; i++) {
      cin >> a[i];
      vector<int> top, bot;
      int lim = sqrt(a[i]);
      for(int j=1; j <= min(a[i], lim+1); j++) {
        top.push_back(j);
        bot.push_back((a[i] + j-1) / j);
      }
      while(!empty(bot) && bot.back() <= top.back()) {
        bot.pop_back();
      }
      bot.insert(end(bot), rbegin(top), rend(top));

      //cerr << a[i] << ":"; for(int it:bot) cerr << " " << it;
      //cerr << nl;

      int m = size(bot);
      vector<Int> ndp(m);
      for(int j=0, k=0; j<m; j++) {
        int cur = a[i] / bot[j];
        while(k+1 < size(div) && (a[i-1] + div[k+1] - 1) / div[k+1] <= cur) {
          k++;
        }
        ndp[j] = dp[k] + Int(i) * (bot[j] - 1);
      }
      ans += ndp.back();
      //cerr << "add " << ndp.back() << " @ " << i << nl;
      dp = move(ndp);
      div = move(bot);
    }
    cout << ans << nl;
  }

  return 0;
}
