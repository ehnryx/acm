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

  int n, m, k;
  cin >> n >> m >> k;
  vector adj(n, vector<bool>(n));
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    adj[a][b] = adj[b][a] = 1;
  }

  vector<int> transition(1<<n);
  for(int bm=0; bm<1<<n; bm++) {
    int sm = 0;
    for(int i=0; i<n; i++) {
      if(!(bm & 1<<i)) continue;
      for(int j=0; j<n; j++) {
        if(!adj[i][j]) continue;
        sm |= 1 << j;
      }
    }
    transition[bm] = sm;
  }

  const int T = n + 7;
  int last = -1;
  vector dp(T + 1, vector<pair<int,int>>(1<<n, pair(-1, -1)));
  dp[0][(1<<n)-1] = pair(0, 0);
  for(int step=0; step<T && last == -1; step++) {
    for(int bm=0; bm<1<<n && last == -1; bm++) {
      if(dp[step][bm].first == -1) continue;
      for(int sm=bm; sm; sm=(sm-1)&bm) {
        if(__builtin_popcount(sm) > k) continue;
        int to = transition[bm ^ sm];
        dp[step + 1][to] = pair(bm, sm);
        if(to == 0) {
          last = step + 1;
          break;
        }
      }
    }
  }

  if(last == -1) {
    cout << -1 << nl;
  } else {
    vector<string> ans;
    for(int i=last, bm=0; i>0; i--) {
      string cur;
      for(int j=0; j<n; j++) {
        if(dp[i][bm].second & 1<<j) {
          cur.push_back(j + 'a');
        }
      }
      ans.push_back(cur);
      bm = dp[i][bm].first;
    }
    reverse(begin(ans), end(ans));
    cout << size(ans) << nl;
    for(const string& s : ans) {
      cout << s << nl;
    }
  }

  return 0;
}
