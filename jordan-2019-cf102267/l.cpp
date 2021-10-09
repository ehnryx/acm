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

  vector<pair<int, int>> ans;

  string s;
  cin >> s;
  cerr << s << nl;

  string t;
  for(char c : s) {
    if(c == 'a' || c == 'b') {
      t.push_back(c);
      continue;
    }
    if(empty(t)) {
      cout << -1 << nl;
      return 0;
    }
    // ac
    if(t.back() == 'a') {
      ans.emplace_back(3, size(t));
      t += "ba";
      continue;
    }
    if(size(t) == 1) {
      cout << -1 << nl;
      return 0;
    }
    // abc
    if(t[size(t)-2] == 'a') {
      t.pop_back();
      t.pop_back();
      ans.emplace_back(4, size(t));
      continue;
    }
    // bbc
    ans.emplace_back(2, size(t)-2);
    ans.emplace_back(3, size(t)-1);
    ans.emplace_back(4, size(t));
  }
  cerr << t << nl;

  string u;
  for(char c : t) {
    if(c == 'a') {
      u.push_back(c);
      continue;
    }
    if(empty(u)) {
      cout << -1 << nl;
      return 0;
    }
    ans.emplace_back(2, size(u));
    u.pop_back();
    ans.emplace_back(4, size(u));
  }
  cerr << u << nl;

  for(char c : u) {
    ans.emplace_back(1, 0);
    ans.emplace_back(2, 1);
    ans.emplace_back(4, 0);
  }

  cout << size(ans) << nl;
  for(auto [v, i] : ans) {
    cout << v << " " << i+1 << nl;
  }

  return 0;
}
