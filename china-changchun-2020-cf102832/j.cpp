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

bool good(int left, int right, int lb, int rb) {
  bool ok = false;
  if(right <= lb || rb <= left) ok = true;
  if(left <= lb && rb <= right) ok = true;
  if(lb <= left && right <= rb) ok = true;
  return ok;
}

vector<vector<pair<int,int>>> all;
int cnt = 0;
void generate(int n, int r, vector<pair<int,int>> have) {
  if(n == -1) { all.push_back(have); return; }
  if(r == 0) return generate(n-1, 5, have);
  generate(n, r-1, have);
  int left = n - r;
  int right = n + r;
  bool ok = left < 5;
  for(auto [c, v] : have) {
    int lb = c - v;
    int rb = c + v;
    ok &= good(left, right, lb, rb);
  }
  if(ok) {
    have.emplace_back(n, r);
    generate(n, r-1, have);
  }
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

  generate(10, 5, {});
  sort(begin(all), end(all));
  assert(all[0].empty());
  int m = size(all);
  //cerr << "valid: " << m << nl;

  vector transition(m, vector<int>(6));
  vector allowed(m, vector<bool>(6));
  vector<int> shift(m);
  for(int j=0; j<m; j++) {
    for(int r=1; r<=5; r++) {
      auto nxt = all[j];
      nxt.emplace_back(0, r);
      transition[j][r] = lower_bound(begin(all), end(all), nxt) - begin(all);
      //assert(transition[j][r] < m && all[transition[j][r]] == nxt);
      bool ok = true;
      for(auto [x, v] : all[j]) {
        ok &= good(-r, r, x - v, x + v);
        ok &= pair(0, r) < pair(x, v);
      }
      allowed[j][r] = ok;
    }
    vector<pair<int,int>> nxt;
    for(auto [x, v] : all[j]) {
      x += 1;
      if(x - v < 5) {
        nxt.emplace_back(x, v);
      }
    }
    shift[j] = lower_bound(begin(all), end(all), nxt) - begin(all);
    assert(shift[j] < m && all[shift[j]] == nxt);
  }

  int n, k;
  cin >> n >> k;
  vector<pair<int,int>> have;
  for(int i=0; i<k; i++) {
    int c, r;
    cin >> c >> r;
    have.emplace_back(c, r);
  }

  vector dp(2, vector(6, vector<int>(m)));
  dp[1][0][0] = 1;
  for(int i=1; i<n; i++) {
    int t = i & 1;
    for(int r=5; r>=1; r--) {
      bool put = (0 <= i-r && i+r <= n);
      bool eq = false;
      for(auto [j, v] : have) {
        put &= good(i - r, i + r, j - v, j + v);
        eq |= (tie(i, r) == tie(j, v));
      }
      //cerr << i << " " << r << " -> put eq : " << put << " " << eq << nl;
      for(int j=0; j<m; j++) {
        int pr = r+1 <= 5 ? r+1 : 0;
        dp[t][r][j] = (eq ? 0 : dp[t][pr][j]);
      }
      if(!put) continue;

      for(int j=0; j<m; j++) {
        if(allowed[j][r]) {
          int nj = transition[j][r];
          int pr = r+1 <= 5 ? r+1 : 0;
          dp[t][r][nj] = add(dp[t][r][nj], dp[t][pr][j]);
        }
      }
    }

    // bring i to i+1;
    fill(begin(dp[t^1][0]), end(dp[t^1][0]), 0);
    for(int j=0; j<m; j++) {
      int nj = shift[j];
      dp[t^1][0][nj] = add(dp[t^1][0][nj], dp[t][1][j]);
    }
    //cerr << i+1 << " :: " << accumulate(begin(dp[t^1][0]), end(dp[t^1][0]), (ll)0) << nl;
  }

  int ans = 0;
  for(int j=0; j<m; j++) {
    ans = add(ans, dp[n&1][0][j]);
  }
  cout << ans << nl;

  return 0;
}
