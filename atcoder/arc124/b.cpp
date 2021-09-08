#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
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
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  for(int i=0; i<n; i++) {
    cin >> b[i];
  }

  vector<int> ans;
  for(int i=0; i<n; i++) {
    int x = a.front() ^ b[i];
    multiset<int> have(begin(b), end(b));
    have.erase(have.find(b[i]));
    bool ok = true;
    for(int j=1; j<n; j++) {
      auto it = have.find(a[j] ^ x);
      if (it == have.end()) {
        ok = false;
        break;
      }
      have.erase(it);
    }
    if(ok) {
      ans.push_back(x);
    }
  }

  sort(begin(ans), end(ans));
  ans.resize(unique(begin(ans), end(ans)) - begin(ans));
  cout << ans.size() << nl;
  for(int x : ans) {
    cout << x << nl;
  }

  return 0;
}
