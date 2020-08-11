//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "pipe"

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

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

ld lp_dist(const pt& a, const pt& b, const pt& p) {
  return cp(b-a, p-a) / abs(b-a);
}

ld get_dist(int a, int b, int x, int y, int s, int t) {
  pt A(a, b), B(x, y), C(s, t);
  return abs(lp_dist(A, B, C));
}

const int N = 200 + 1;
ld cost[N][2];
ld dp[N][N];
pair<int,int> pre[N][N];

bool update(ld& x, const ld& v) {
  x = min(x, v);
  return x == v;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int n, c;
  cin >> n >> c;
  vector<tuple<int,int,int,int>> lines;
  for(int t=0; t<2; t++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    lines.emplace_back(a, b, x, y);
  }

  for(int i=1; i<=n; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    for(int t=0; t<2; t++) {
      cost[i][t] = z * apply(get_dist, tuple_cat(lines[t], tie(x, y)));
    }
  }

  fill(&dp[0][0], &dp[0][0]+N*N, INFLL);

  dp[0][0] = 0;
  for(int i=0; i<=n; i++) {
    for(int j=0; i+j<=n; j++) {
      if(i && update(dp[i][j], dp[i-1][j] + cost[i+j][0])) {
        pre[i][j] = make_pair(i-1, j);
      }
      if(j && update(dp[i][j], dp[i][j-1] + cost[i+j][1])) {
        pre[i][j] = make_pair(i, j-1);
      }
    }
  }

  ld best = INFLL;
  for(int i=0; i<=n; i++) {
    if(abs(n-i - i) <= c) {
      best = min(best, dp[i][n-i]);
    }
  }

  for(int i=0; i<=n; i++) {
    if(abs(n-i - i) <= c && dp[i][n-i] == best) {
      vector<int> ans;
      for(int a=i, b=n-i; a || b; ) {
        if(pre[a][b].first < a) {
          ans.push_back(1);
          a--;
        } else {
          ans.push_back(2);
          b--;
        }
      }
      reverse(ans.begin(), ans.end());
      for(int it : ans) {
        cout << it << " ";
      }
      cout << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
