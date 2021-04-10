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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace SuffixArray {
  const int L = 19; const int N = 1<<L; const int A = 1e9+7;
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

  string s;
  cin >> s;
  int n = s.size();
  SuffixArray::build(s);
  s.push_back(0);

  vector<vector<pair<int,int>>> query(n + 1);
  vector<vector<int>> rem(n + 1);

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    query[b-1].emplace_back(a-1, i);
  }

  vector<int> ans(m);
  set<int> active;
  stack<int> alive;
  for(int i=0; i<n; i++) {
    while(!alive.empty()) {
      int j = alive.top();
      int len = SuffixArray::lcp(i, j);
      if(s[i+len] < s[j+len]) break;
      rem[i+len].push_back(j); // mark for removal
      alive.pop(); // should only mark once
    }
    active.insert(i);
    alive.push(i);
    for(int j : rem[i]) {
      active.erase(j);
    }
    for(auto [l, j] : query[i]) {
      ans[j] = *active.lower_bound(l) + 1;
    }
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
