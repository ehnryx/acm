#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const int N = 11;
int r[N], c[N];

vector<vector<int>> parts;
vector<int> popcnts[N];

void partition(int m, int n, int t, char op, vector<int>& cur) {
  if(m == 0) {
    if(op == '+' || (op == '*' && t == 1)) {
      parts.push_back(cur);
    }
    return;
  }

  for(int d=1; d<=(cur.empty()?n:cur.back()); d++) {
    if(op == '+' && d + m-1 <= t && d + n*(m-1) >= t) {
      cur.push_back(d);
      partition(m-1, n, t-d, op, cur);
      cur.pop_back();
    }
    else if(op == '*' && t % d == 0) {
      cur.push_back(d);
      partition(m-1, n, t/d, op, cur);
      cur.pop_back();
    }
  }
}

ll dp[1<<N][N];
ll solve(int bm, int i, const vector<int>& vals) {
  if(dp[bm][i] != -1) return dp[bm][i];
  if(i == vals.size()) return dp[bm][i] = 1;

  ll res = 0;
  for(int sm : popcnts[vals[i]]) {
    if((bm & sm) != sm) continue;
    res += solve(bm^sm, i+1, vals);
  }
  return dp[bm][i] = res;
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

  int n, m, t; char op;
  cin >> n >> m >> t >> op;
  for(int i=0; i<m; i++) {
    cin >> r[i] >> c[i];
  }

  if(op == '-') {
    int ans = 0;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<i; j++) {
        if(i - j == t) {
          ans++;
        }
      }
    }
    cout << 2 * ans << nl;
    return 0;
  }

  if(op == '/') {
    int ans = 0;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<i; j++) {
        if(i % j == 0 && i / j == t) {
          ans++;
        }
      }
    }
    cout << 2 * ans << nl;
    return 0;
  }

  vector<int> _cur;
  partition(m, n, t, op, _cur);

  for(int bm=0; bm<1<<m; bm++) {
    int row = 0;
    int col = 0;
    for(int i=0; i<m; i++) {
      if(bm & 1<<i) {
        row |= 1<<r[i];
        col |= 1<<c[i];
      }
    }
    int cnt = __builtin_popcount(bm);
    if(__builtin_popcount(row) == cnt && __builtin_popcount(col) == cnt) {
      popcnts[cnt].push_back(bm);
    }
  }

  ll ans = 0;
  for(const auto& part : parts) {
    map<int,int> freq;
    for(int v : part) {
      freq[v]++;
    }
    vector<int> vals;
    for(auto [_, c] : freq) {
      vals.push_back(c);
    }
    memset(dp, -1, sizeof dp);
    ans += solve((1<<m)-1, 0, vals);
  }
  cout << ans << nl;

  return 0;
}
