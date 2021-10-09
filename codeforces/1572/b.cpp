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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }

    vector<int> ans;
    for(int i=1; i+2<=n; i++) {
      if(a[i] == 0 && a[i+1] && a[i+1] != a[i+2] && i+3 <= n) {
        ans.push_back(i+1);
        a[i+1] = a[i+2] = a[i+3] = a[i+1] ^ a[i+2] ^ a[i+3];
      }
      if(a[i] == 0 && a[i+1] && a[i+1] == a[i+2]) {
        ans.push_back(i);
        a[i] = a[i+1] = a[i+2] = a[i] ^ a[i+1] ^ a[i+2];
      }
    }
    for(int i=n; i>=3; i--) {
      if(a[i] == 0 && a[i-1] && a[i-1] != a[i-2] && i-3 >= 1) {
        ans.push_back(i-3);
        a[i-3] = a[i-2] = a[i-1] = a[i-3] ^ a[i-2] ^ a[i-1];
      }
      if(a[i] == 0 && a[i-1] && a[i-1] == a[i-2]) {
        ans.push_back(i-2);
        a[i-2] = a[i-1] = a[i] = a[i] ^ a[i-1] ^ a[i-2];
      }
    }
    for(int i=1; i+2<=n; i++) {
      if(a[i] && (a[i] ^ a[i+1] ^ a[i+2]) == 0) {
        ans.push_back(i);
        a[i] = a[i+1] = a[i+2] = 0;
      }
    }
    for(int i=1; i+2<=n; i++) {
      if(a[i] == 0 && a[i+1] && a[i+1] != a[i+2] && i+3 <= n) {
        ans.push_back(i+1);
        a[i+1] = a[i+2] = a[i+3] = a[i+1] ^ a[i+2] ^ a[i+3];
        ans.push_back(i);
        a[i] = a[i+1] = a[i+2] = a[i] ^ a[i+1] ^ a[i+2];
      }
    }
    for(int i=n; i>=3; i--) {
      if(a[i] == 0 && a[i-1] && a[i-1] != a[i-2] && i-3 >= 1) {
        ans.push_back(i-3);
        a[i-3] = a[i-2] = a[i-1] = a[i-3] ^ a[i-2] ^ a[i-1];
        ans.push_back(i-2);
        a[i-2] = a[i-1] = a[i] = a[i] ^ a[i-1] ^ a[i-2];
      }
    }

    if(*max_element(begin(a), end(a))) {
      cout << "NO" << nl;
    } else {
      cout << "YES" << nl;
      cout << size(ans) << nl;
      for(int i : ans) {
        cout << i << " ";
      }
      cout << nl;
      assert(size(ans) <= n);
    }
  }

  return 0;
}
