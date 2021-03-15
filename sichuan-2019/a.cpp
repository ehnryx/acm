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

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  set<int> open;
  for(int i=0; i<m; i++) {
    open.insert(i);
  }

  unordered_map<string,vector<int>> all;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    if(all.count(s + "3")) continue;
    if(all[s].size() == k-1) {
      for(int j : all[s]) {
        open.insert(j);
      }
      all[s].clear();
      if(all[s + "2"].size() == k-1) {
        for(int j : all[s + "2"]) {
          open.insert(j);
        }
        all[s + "2"].clear();
        all[s + "3"].push_back(*open.begin());
        open.erase(open.begin());
      } else {
        all[s + "2"].push_back(*open.begin());
        open.erase(open.begin());
      }
    } else if(!open.empty()) {
      all[s].push_back(*open.begin());
      open.erase(open.begin());
    }
  }

  vector<string> ans(m, "-1");
  for(const auto& [s, v] : all) {
    for(int j : v) {
      ans[j] = s;
    }
  }

  for(int i=0; i<m; i++) {
    cout << " " << ans[i];
  }
  cout << nl;
}

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

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ":";
    solve();
  }

  return 0;
}
