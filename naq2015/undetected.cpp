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

int sqr(int x) {
  return x*x;
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
  vector<int> x(n), y(n), r(n);
  vector<vector<int>> adj(n);
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i] >> r[i];
    if(x[i]-r[i] < 0) {
      adj[i].push_back(n);
    }
    if(x[i]+r[i] > 200) {
      adj[i].push_back(n+1);
    }
    for(int j=0; j<i; j++) {
      if(sqr(x[i]-x[j]) + sqr(y[i]-y[j]) < sqr(r[i]+r[j])) {
        adj[i].push_back(j);
      }
    }
  }

  vector<int> dsu(n+2, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    if(find(i) != find(j)) {
      dsu[find(i)] = find(j);
    }
  };

  for(int i=0; i<n; i++) {
    for(int j : adj[i]) {
      link(i, j);
    }
    if(find(n) == find(n+1)) {
      cout << i << nl;
      return 0;
    }
  }
  assert(false);

  return 0;
}
