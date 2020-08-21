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

  for(int n, m; cin >> n >> m; ) {
    vector<int> dsu(2*n+1, -1);
    vector<ll> sum(2*n+1);
    vector<set<int>> all(2*n+1);

    function<int(int)> find = [&](int i) {
      if(dsu[i] == -1) return i;
      return dsu[i] = find(dsu[i]);
    };

    auto link = [&](int i, int j) {
      i = find(i); j = find(j);
      if(i == j) return;
      if(all[i].size() > all[j].size()) swap(i, j);
      for(int v : all[i]) {
        dsu[v] = j;
        all[j].insert(v);
        sum[j] += v;
      }
    };

    auto move_to = [&](int i, int j) {
      int r = find(i); j = find(j);
      if(r == j) return;
      all[r].erase(i);
      sum[r] -= i;
      dsu[i] = j;
      sum[j] += i;
      all[j].insert(i);
    };

    for(int i=1; i<=n; i++) {
      dsu[i] = i+n;
      sum[i+n] = i;
      all[i+n].insert(i);
    }

    while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
        int a, b;
        cin >> a >> b;
        link(a, b);
      } else if(t == 2) {
        int a, b;
        cin >> a >> b;
        move_to(a, b);
      } else {
        int a;
        cin >> a;
        a = find(a);
        cout << all[a].size() << " " << sum[a] << nl;
      }
    }
  }

  return 0;
}
