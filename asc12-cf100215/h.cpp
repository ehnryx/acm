//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "police"

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

const int N = 1e3 + 1;
int dsu[N];

int find(int i) {
  if(dsu[i] == 0) return i;
  return dsu[i] = find(dsu[i]);
}

bool link(int i, int j) {
  i = find(i);
  j = find(j);
  if(i == j) return false;
  dsu[i] = j;
  return true;
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

  int n, m, r;
  cin >> n >> m >> r;
  vector<int> a(r), b(r), c(r);
  for(int i=0; i<r; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }

  vector<tuple<int,int,int>> edges;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      int best = INF;
      int cost = 0;
      int cnt = 0;
      for(int k=0; k<r; k++) {
        int cur = abs(i-a[k]) + abs(j-b[k]);
        if(cur < best) {
          best = cur;
          cnt = 0;
          cost = c[k];
        }
        cnt += (cur == best);
      }
      if(cnt == 1) {
        edges.emplace_back(cost, i, j);
      }
    }
  }
  sort(edges.begin(), edges.end());

  vector<pair<int,int>> res;
  ll ans = 0;
  for(auto [cost, u, v] : edges) {
    if(link(u, v+n)) {
      ans += cost;
      res.emplace_back(u, v);
    }
  }

  if(res.size() < n+m-1) {
    cout << -1 << nl;
  } else {
    cout << res.size() << " " << ans << nl;
    for(auto [u, v] : res) {
      cout << u << " " << v << nl;
    }
  }

  return 0;
}
