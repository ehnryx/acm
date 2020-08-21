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

const int M = 5e5 + 1;
int dsu[M], sz[M];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}
void link(int i, int j) {
  i = find(i); j = find(j);
  if(i == j) return;
  dsu[i] = j;
  sz[j] += sz[i];
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

  fill(dsu, dsu+M, -1);
  fill(sz, sz+M, 1);

  int n;
  cin >> n;
  int ans = 0;
  for(int i=0; i<n; i++) {
    int m;
    cin >> m;
    set<int> seen;
    int cnt = 0;
    for(int j=0; j<m; j++) {
      int v;
      cin >> v;
      v = find(v);
      if(seen.count(v)) continue;
      seen.insert(v);
      cnt += sz[v];
    }
    if(cnt == m) {
      ans++;
      for(int v : seen) {
        link(v, *seen.begin());
      }
    }
  }

  cout << ans << nl;

  return 0;
}
