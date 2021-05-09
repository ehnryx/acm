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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



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

  int n;
  cin >> n;
  int axes = 0;
  vector<tuple<int,int,int>> v;
  for(int i=0; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if(a == 0 && b == 0) axes |= 0b001;
    if(b == 0 && c == 0) axes |= 0b100;
    if(c == 0 && a == 0) axes |= 0b010;
    v.emplace_back(a, b, c);
  }
  sort(begin(v), end(v));
  if(__builtin_popcount(axes) < 3) {
    cout << "Infinity" << nl;
    return 0;
  }

  set<pair<int,int>> pareto;
  pareto.insert(pair(INF, INF));
  multiset<int> maxv;
  maxv.insert(INF + INF);

  using s_it = set<pair<int,int>>::iterator;
  function<void(pair<int,int>)> insert = [&](pair<int,int> p) {
    if(p.first > 0 && p.second > 0) {
      maxv.insert(p.first + p.second);
    }
    pareto.insert(p);
  };
  function<s_it(s_it)> remove = [&](s_it rem) {
    if(rem->first > 0 && rem->second > 0) {
      maxv.erase(maxv.find(rem->first + rem->second));
    }
    return pareto.erase(rem);
  };

  ll ans = 0;
  for(auto [x, y, z] : v) {
    if(x > 0 && !empty(maxv)) {
      ans = max(ans, (ll)x + *rbegin(maxv));
    }
    auto it = pareto.upper_bound(pair(y, INF));
    if(it != end(pareto) && it->second <= z) continue;
    int top = it->second;
    if(it != begin(pareto) && prev(it)->first == y && prev(it)->second >= z) {
      top = prev(it)->second;
      it = remove(prev(it));
    }
    int right = it->first;
    while(it != end(pareto) && it->second >= z) {
      right = it->first;
      it = remove(it);
    }
    insert(pair(y, top));
    insert(pair(right, z));
  }
  cout << ans - 3 << nl;

  return 0;
}
