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

  for(string s; cin >> s && s != "0"; ) {
    vector<char> variable, unary, binary;
    for(char c : s) {
      if(islower(c)) {
        variable.push_back(c);
      } else if(c == 'N') {
        unary.push_back(c);
      } else {
        binary.push_back(c);
      }
    }
    if(variable.empty()) {
      cout << "no WFF possible" << nl;
    } else {
      string ans;
      ans.push_back(variable.back());
      variable.pop_back();
      while(!variable.empty() && !binary.empty()) {
        ans.push_back(variable.back());
        ans.push_back(binary.back());
        variable.pop_back();
        binary.pop_back();
      }
      ans.insert(ans.end(), unary.begin(), unary.end());
      reverse(ans.begin(), ans.end());
      cout << ans << nl;
    }
  }

  return 0;
}
