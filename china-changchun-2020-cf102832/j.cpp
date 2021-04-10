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
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int add(int a, int b) {
  return a+b < MOD ? a+b : a+b - MOD;
}

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

  int n, m;
  cin >> n >> m;
  set<pair<int,int>> must;
  vector<pair<int,int>> circles;
  for(int i=0; i<m; i++) {
    int c, r;
    cin >> c >> r;
    must.insert(pair(c-r, c+r));
  }

  vector<pair<int,int>> all;
  for(int i=1; i<n; i++) {
    for(int j=1; j<=5; j++) {
      if(0 <= i-j && i+j <= n) {
        all.emplace_back(i-j, i+j);
      }
    }
  }
  sort(begin(all), end(all), [](const auto& x, const auto& y) {
    if(x.first != y.first) return x.first < y.first;
    else return x.second > y.second;
  });
  all.insert(begin(all), pair(0, 42));

  const int L = 11;
  int len = size(all);

  vector dp(len, vector<int>(1<<L));
  dp[0][0] = 1;
  for(int i=1; i<len; i++) {
    if(!must.count(all[i])) {
      if(all[i].first == all[i-1].first) {
        dp[i] = dp[i-1];
      } else {
        for(int bm=0; bm<1<<(L-1); bm++) {
          dp[i][bm] = add(dp[i-1][bm<<1], dp[i-1][bm<<1|1]);
        }
      }
    }

    bool put = true;
    for(auto [l, r] : must) {
      bool ok = false;
      ok |= (all[i].second <= l || r <= all[i].first);
      ok |= (l <= all[i].first && all[i].second <= r);
      ok |= (all[i].first <= l && r <= all[i].second);
      put &= ok;
    }
    if(!put) {
      continue;
    }

    int diam = all[i].second - all[i].first;
    for(int bm=0; bm<1<<L; bm++) {
      int om = (bm >> (all[i].first != all[i-1].first)) | 1 << diam;
      bool bad = false;
      for(int j=1; j<diam; j++) {
        if(om & 1<<j) {
          bad = true;
          break;
        }
      }
      if(bad) continue;
      dp[i][om] = add(dp[i][om], dp[i-1][bm]);
    }
  }

  int ans = 0;
  for(int bm=0; bm<1<<L; bm++) {
    ans = add(ans, dp[len-1][bm]);
  }
  cout << ans << nl;

  return 0;
}
