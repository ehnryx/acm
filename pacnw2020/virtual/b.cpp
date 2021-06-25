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

  int n, k;
  cin >> n >> k;
  vector<int> a;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    int bm = 0;
    for(int j=0; j<k; j++) {
      if(s[j] == 'T') {
        bm |= 1 << j;
      }
    }
    a.push_back(bm);
  }
  int ans = 0;
  for(int bm=0; bm<1<<k; bm++) {
    int bad = 0;
    for(int it : a) {
      bad = max(bad, __builtin_popcount(it ^ bm));
    }
    ans = max(ans, k - bad);
  }
  cout << ans << nl;

  return 0;
}
