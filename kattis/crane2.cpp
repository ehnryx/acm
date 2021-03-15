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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }

    vector<pair<int,int>> ans;
    for(int i=1; i<=n; i++) {
      int j = find(a.begin() + i, a.end(), i) - a.begin();
      while(j != i) {
        if((j - i) % 2 == 0) {
          ans.emplace_back(i+1, j);
        } else {
          ans.emplace_back(i, j);
        }
        int len = (j - i + 1) / 2;
        assert(len > 0);
        for(int k=0; k<len; k++) {
          swap(a[j-k], a[j-k-len]);
        }
        j -= len;
      }
    }

    cout << ans.size() << nl;
    for(auto [x, y] : ans) {
      cout << x << " " << y << nl;
    }
  }

  return 0;
}
