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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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

  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(m);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<m; i++) {
    cin >> b[i];
  }

  set<pair<int,int>> seen;
  priority_queue<tuple<int,int,int>> order;
  for(int i=1; i<n; i++) {
    order.emplace(a[i-1] - a[i], i-1, i);
    seen.insert(pair(i-1, i));
  }

  vector<int> dists;
  while(!order.empty() && dists.size() < m) {
    auto [d, l, r] = order.top();
    order.pop();
    dists.push_back(-d);
    if(l > 0 && seen.insert(pair(l-1, r)).second) {
      order.emplace(a[l-1] - a[r], l-1, r);
    }
    if(r+1 < n && seen.insert(pair(l, r+1)).second) {
      order.emplace(a[l] - a[r+1], l, r+1);
    }
  }

  sort(b.begin(), b.end());
  bool ok = (dists.size() == m);
  for(int i=0; i<m && ok; i++) {
    ok &= (dists[i] <= b[i]);
  }
  cout << (ok ? "yes" : "no") << nl;

  return 0;
}
