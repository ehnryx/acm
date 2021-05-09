#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
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

  int n;
  cin >> n;
  vector<pair<int,int>> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(b+1, a+1);
  }
  v.emplace_back(4*n, 4*n);
  sort(begin(v), end(v));

  static const int L = 18;
  vector minv(L, vector<int>(n+1)), maxv(L, vector<int>(n+1));
  for(int i=0; i<=n; i++) {
    minv[0][i] = maxv[0][i] = v[i].second;
  }
  for(int j=1; j<L; j++) {
    for(int i=0; i+(1<<j)-1 <= n; i++) {
      minv[j][i] = min(minv[j-1][i], minv[j-1][i+(1<<(j-1))]);
      maxv[j][i] = max(maxv[j-1][i], maxv[j-1][i+(1<<(j-1))]);
    }
  }
  function<int(int,int)> min_query = [=](int l, int r) {
    int j = 31 - __builtin_clz(r-l+1);
    return min(minv[j][l], minv[j][r-(1<<j)+1]);
  };
  function<int(int,int)> max_query = [=](int l, int r) {
    int j = 31 - __builtin_clz(r-l+1);
    return max(maxv[j][l], maxv[j][r-(1<<j)+1]);
  };

  vector<int> dp(4*n + 1, -1);
  dp[0] = 0;
  set<int> good;
  for(int i=0; i<=4*n; i++) {
    int j = lower_bound(begin(v), end(v), pair(i, 0)) - begin(v);
    if(j == 0) {
      dp[i] = 0;
      good.insert(i);
    } else {
      int r = min_query(j, n) - 1;
      int l = max_query(0, j-1);
      auto it = good.lower_bound(l);
      if(it != end(good) && *it <= r) {
        dp[i] = *it;
        good.insert(i);
      }
    }
  }

  if(dp[4*n] == -1) {
    cout << -1 << nl;
  } else {
    vector<int> ans;
    for(int i=dp[4*n]; i>0; i=dp[i]) {
      ans.push_back(i - 1);
    }
    cout << size(ans) << nl;
    for(int it : ans) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
