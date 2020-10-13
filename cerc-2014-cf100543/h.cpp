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

  vector<pair<int,int>> nums = {
            {3, 1}        , // zero
    {0, 0}, {0, 1}, {0, 2},
    {1, 0}, {1, 1}, {1, 2},
    {2, 0}, {2, 1}, {2, 2},
  };
  vector<int> valid;
  const int N = 400;
  for(int v=1; v<=N; v++) {
    string s = to_string(v);
    bool ok = true;
    for(int i=1; i<s.size(); i++) {
      int a = s[i-1] - '0';
      int b = s[i] - '0';
      ok &= (nums[a].first <= nums[b].first);
      ok &= (nums[a].second <= nums[b].second);
    }
    if(ok) valid.push_back(v);
  }

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    int ans = INF;
    for(int i : valid) {
      if(abs(i-n) < abs(ans-n)) {
        ans = i;
      }
    }
    cout << ans << nl;
  }

  return 0;
}
