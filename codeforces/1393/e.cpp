//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9 + 7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SuffixArray {
  const int L = 15; const int N = 1<<L; const int A = 1e9+7;
  int p[L+1][N]; pair<ll,int> m[N]; int last, n;
  /// replace pair<ll,int> ^here with pair<pair<int,int>,int> for 32-bit
  void build(const string& s) { n = s.size();
    if(n <= 1) { p[0][0] = last = 0; return; }
    for (int i = 0; i < n; i++) p[0][i] = s[i];
    for (int j = 1, v = 1; j < n; j *= 2, v++) {
      for (int i = 0; i < n; i++) {
        m[i] = { (ll)p[v-1][i] * A + (i+j<n ? p[v-1][i+j] : -1), i };
      } sort(m, m+n);
      for (int i = 0; i < n; i++) {
        p[v][m[i].second] = (i > 0 && m[i].first == m[i-1].first) ?
          p[v][m[i-1].second] : i; } last = v; } }
  int* idx() { return p[last]; }
  int lcp(int i, int j) {
    int len = 0; if (i == j) return n - i;
    for (int k = last; k >= 0 && i < n && j < n; k--) {
      if (p[k][i] == p[k][j]) { i += 1<<k; j += 1<<k; len += 1<<k; }
    } return len; }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<string> s(n+1);
  vector<int> start(n+1);
  string all;
  for(int i=1; i<=n; i++) {
    cin >> s[i];
    start[i] = all.size();
    all += s[i];
  }
  SuffixArray::build(all);

  function<bool(int,int,int,int,function<bool(char,char)>)> smaller =
    [&](int i, int j, int o, int k, function<bool(char,char)> cmp) {
    if(i == 0) return true;
    if(o == 0) return false;
    if(j > k) return !smaller(o, k, i, j, less<char>());

    int lcp = SuffixArray::lcp(start[i], start[o]);
    if(lcp < min(j, k)) return cmp(s[i][lcp], s[o][lcp]);

    lcp = SuffixArray::lcp(start[i] + j + 1, start[o] + j);
    if(j+lcp < k) {
      if(j+1+lcp < s[i].size()) return cmp(s[i][j+1+lcp], s[o][j+lcp]);
      else return true;
    }
    if(k+1 >= s[i].size()) {
      return true;
    }

    lcp = SuffixArray::lcp(start[i] + k + 1, start[o] + k + 1);
    if(k+1+lcp < min(s[i].size(), s[o].size())) {
      return cmp(s[i][k+1+lcp], s[o][k+1+lcp]);
    } else if(k+1+lcp < s[i].size()) {
      return false;
    } else if(k+1+lcp < s[o].size()) {
      return true;
    } else {
      return s[i].size() <= s[o].size();
    }
  };

  vector<vector<int>> dp(n+1);
  dp[0] = {1};
  for(int i=1; i<=n; i++) {
    dp[i].resize(s[i].size() + 1);
    for(int j=0; j<=s[i].size(); j++) {
      for(int k=0; k<=s[i-1].size(); k++) {
        if(smaller(i-1, k, i, j, less_equal<char>())) {
          dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD;
        }
      }
    }
  }

  int ans = 0;
  for(int i=0; i<=s[n].size(); i++) {
    ans = (ans + dp[n][i]) % MOD;
  }
  cout << ans << nl;

  return 0;
}
