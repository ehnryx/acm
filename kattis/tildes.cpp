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

template <class F>
struct y_combinator_result {
  F fun_;
  template<class T>
  explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template<class F>
decltype(auto) y_combinator(F &&fun) {
  return y_combinator_result<std::decay_t<F>>(std::forward<F>(fun));
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

  int n, m;
  cin >> n >> m;

  vector<int> sz(n+1, 1);
  vector<int> dsu(n+1);
  auto find = y_combinator([&](auto self, int i) -> int {
    if(dsu[i] == 0) return i;
    return dsu[i] = self(dsu[i]);
  });
  auto link = [&](int i, int j) {
    i = find(i);
    j = find(j);
    if(i == j) return;
    dsu[i] = j;
    sz[j] += sz[i];
  };

  while(m--) {
    char t;
    cin >> t;
    if(t == 's') {
      int a;
      cin >> a;
      a = find(a);
      cout << sz[a] << nl;
    } else {
      int a, b;
      cin >> a >> b;
      link(a, b);
    }
  }

  return 0;
}
