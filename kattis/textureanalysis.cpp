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

  for(int tc=1; ; tc++) {
    string s;
    cin >> s;
    if(s == "END") break;
    s.pop_back();
    if(s.empty()) {
      cout << tc << " " << "EVEN" << nl;
      continue;
    }

    int black = count(s.begin(), s.end(), '*');
    bool ok = (s.size() % black == 0);
    if(ok) {
      int len = s.size() / black;
      string pat = s.substr(0, len);
      for(int i=len; i<s.size(); i+=len) {
        ok &= (s.substr(i, len) == pat);
      }
    }
    cout << tc << " " << (ok ? "EVEN" : "NOT EVEN") << nl;
  }

  return 0;
}
