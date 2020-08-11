//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME sadcactussociety

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
/*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
*/

  int T;
  cin >> T;
  while(T--) {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n), cnt(n+2);
    vector<pair<int,int>> order;
    for(int i=0; i<n; i++) {
      cin >> a[i];
      order.emplace_back(cnt[a[i]]++, i);
    }
    sort(order.begin(), order.end());

    vector<int> ans(n);
    for(int i=1; i<=x; i++) {
      int j = order[n-i].second;
      ans[j] = a[j];
      cnt[a[j]]--;
    }

    int extra = -1;
    for(int i=1; i<=n+1; i++) {
      if(cnt[i] == 0) {
        extra = i;
      }
    }
    cnt[extra] = n-y;
    a.resize(n + n-y, extra);
    ans.resize(n + n-y);

    vector<vector<int>> idx(n+2);
    for(int i=0; i<n+n-y; i++) {
      if(ans[i]) continue;
      idx[a[i]].push_back(i);
    }

    set<pair<int,int>> f;
    order.clear();
    for(int i=1; i<=n+1; i++) {
      if(cnt[i]) {
        f.insert(make_pair(cnt[i], i));
        order.emplace_back(cnt[i], i);
      }
    }
    sort(order.begin(), order.end(), greater<pair<int,int>>());

    for(auto [_, group] : order) {
      cerr<<"do group "<<group<<nl;
      for(int i : idx[group]) {
        if(a[i] == f.rbegin()->second) {
          if(f.size() == 1) {
            break;
          }
          auto it = prev(prev(f.end()));
          auto [count, colour] = *it;
          f.erase(it);
          if(count > 1) {
            f.insert(make_pair(count-1, colour));
          }
          ans[i] = colour;
        } else {
          auto it = prev(f.end());
          auto [count, colour] = *it;
          f.erase(it);
          if(count > 1) {
            f.insert(make_pair(count-1, colour));
          }
          ans[i] = colour;
        }
      }
    }

    if(f.empty()) {
      cout << "YES" << nl;
      for(int i=0; i<n; i++) {
        cout << ans[i] << " ";
      }
      cout << nl;
    } else {
      cout << "NO" << nl;
    }
    cerr<<nl;
  }

  return 0;
}
