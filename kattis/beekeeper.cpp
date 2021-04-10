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

  vector<string> pat = { "aa", "ee", "ii", "oo", "uu", "yy" };
  set<string> want(pat.begin(), pat.end());
  for(int n; cin >> n && n; ) {
    pair<int, string> ans(-1, "");
    for(int i=0; i<n; i++) {
      string s;
      cin >> s;
      int cnt = 0;
      for(int j=1; j<s.size(); j++) {
        cnt += want.count(s.substr(j-1, 2));
      }
      ans = max(ans, pair(cnt, s));
    }
    cout << ans.second << nl;
  }

  return 0;
}
