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

  for(int n; cin >> n && n; ) {
    if(n == 2) {
      cout << "Impossible" << nl;
      continue;
    }

    vector<int> to(n);
    for(int i=1; i<n; i++) {
      to[i] = 2 * i % n;
    }

    vector<bool> vis(n);
    int cycles = 0;
    for(int i=1; i<n; i++) {
      if(vis[i]) continue;
      vis[i] = true;
      for(int j=to[i]; j!=i; j=to[j]) {
        vis[j] = true;
      }
      cycles++;
    }

    vector<int> ans(n, 1);
    if(cycles % 2) {
      for(int i=1; i<n; i++) {
        if(!vis[i]) continue;
        vis[i] = false;
        ans[i] = 0;
        for(int j=to[i], s=1; j!=i; j=to[j], s^=1) {
          vis[j] = false;
          ans[j] = s;
        }
      }
    } else {
      for(int i=1, cnt=0; i<n && cnt<(n-1)/2; i++) {
        if(ans[n-i] != 1) continue;
        ans[i] = 0;
        cnt++;
        for(int j=to[i]; j!=i; j=to[j]) {
          ans[j] = 0;
          cnt++;
        }
      }
    }

    for(int i=1; i<n; i++) {
      cout << ans[i];
    }
    cout << nl;
    assert(*min_element(begin(ans), end(ans)) != *max_element(begin(ans), end(ans)));
  }

  return 0;
}
