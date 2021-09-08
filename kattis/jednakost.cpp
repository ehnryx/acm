#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string s;
  cin >> s;
  int split = s.find('=');
  string a = s.substr(0, split);
  int goal = stoi(s.substr(split + 1));

  int n = a.size();
  vector<int> to(n+1, n);
  for(int i=n-1; i>=0; i--) {
    if(a[i] == '0') {
      to[i] = to[i+1];
    } else {
      to[i] = i;
    }
  }

  vector dp(n+1, vector<pair<unsigned, int>>(goal+1, pair(-2, -1)));
  dp[n][0] = pair(0, 0);
  for(int i=n-1; i>=0; i--) {
    for(int len=1; len<=min(n-i,4); len++) {
      int add = stoi(a.substr(i, len));
      for(int v=add; v<=goal; v++) {
        if(dp[to[i+len]][v-add].first + 1 < dp[i][v].first) {
          dp[i][v] = pair(dp[to[i+len]][v-add].first + 1, (v-add) << 10 | len);
        }
      }
    }
  }

  assert(dp[to[0]][goal].first != -2);
  vector<int> put;
  for(int i=to[0], v=goal; i<n; ) {
    int len = dp[i][v].second & ((1<<10) - 1);
    v = dp[i][v].second >> 10;
    put.push_back(i+len);
    i = to[i+len];
  }
  put.push_back(n);

  string ans;
  for(int i=0, j=0; i<n; i++) {
    if(i == put[j]) {
      ans.push_back('+');
      j++;
    }
    ans.push_back(a[i]);
  }

  cout << ans << "=" << goal << nl;

  return 0;
}
