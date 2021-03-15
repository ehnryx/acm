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

  int n;
  cin >> n;
  vector<int> height(1000 + 7);
  int left = INF;
  int right = -INF;
  for(int i=0; i<n; i++) {
    int l, r, h;
    cin >> l >> r >> h;
    for(int j=l; j<r; j++) {
      height[j] = max(height[j], h);
    }
    left = min(left, l);
    right = max(right, r);
  }

  int len = right - left + 1;
  vector<string> ans(*max_element(height.begin(), height.end()) + 1, string(len, '.'));

  int perim = 0;
  rotate(height.begin(), height.begin() + left, height.end());
  for(int i=0, pre=0; i<len; i++) {
    int cur = height[i];
    ans[cur][i] = '#';
    if(cur > pre) {
      for(int j=pre; j<=cur; j++) {
        ans[j][i] = '#';
      }
    } else {
      for(int j=pre; j>=cur; j--) {
        ans[j][i-1] = '#';
      }
    }
    perim += abs(pre - cur);
    perim += (cur > 0);
    pre = cur;
  }
  ans.front() = string(len, '*');

  cout << perim << nl;
  reverse(ans.begin(), ans.end());
  for(const string& s : ans) {
    cout << s.substr(0, s.size() - 1) << nl;
  }

  return 0;
}
