#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/graph/two_sat.h"

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

void build(two_sat& sat, const vector<pair<int,int>>& x, int dx, int m, int off) {
  int n = size(x);
  for(int i=0, j=0; i<n; i++) {
    while(x[i].first - x[j].first > dx) j++;
    vector<int> top;
    for(int l=j+m, r=i+m; l<r; l/=2, r/=2) {
      if(l&1) top.push_back(l++);
      if(r&1) top.push_back(--r);
    }
    for(int s : top) {
      if(s < m) sat.implies(x[i].second, true, off + s, false);
      else sat.implies(x[i].second, true, x[s-m].second, false);
    }
    int s = i + m;
    sat.implies(x[i].second, true, off + s/2, true);
    for(s/=2; s>1; s/=2) {
      sat.implies(off + s, true, off + s/2, true);
    }
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

  int T;
  cin >> T;
  while(T--) {
    int n, dx, dy;
    cin >> n >> dx >> dy;
    int m = 1 << (32 - __builtin_clz(2*n-1));
    two_sat sat(2*n + 2*m);

    vector<pair<int,int>> x, y;
    for(int i=0; i<n; i++) {
      int k;
      cin >> k;
      if(k == 1) {
        int a, b;
        cin >> a >> b;
        x.emplace_back(a, 2*i);
        y.emplace_back(b, 2*i);
        x.emplace_back(a, 2*i + 1);
        y.emplace_back(b, 2*i + 1);
      } else {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        x.emplace_back(a, 2*i);
        y.emplace_back(b, 2*i);
        x.emplace_back(c, 2*i + 1);
        y.emplace_back(d, 2*i + 1);
      }
      sat.or_clause(2*i, true, 2*i + 1, true);
    }
    sort(begin(x), end(x));
    sort(begin(y), end(y));
    build(sat, x, dx, m, 2*n);
    build(sat, y, dy, m, 2*n + m);

    if(sat.solve()) {
      cout << "Yes" << nl;
    } else {
      cout << "No" << nl;
    }
  }

  return 0;
}
