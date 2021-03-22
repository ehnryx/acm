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
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";
    string s, t;
    cin >> s >> t;
    int n = s.size();

    vector<int> match(n+1);
    for(int i=n-1; i>=0; i--) {
      match[i] = match[i+1] + (s[i] != t[i]);
    }

    string ans;
    for(int i=0, sc=0, tc=0; i<n; i++) {
      for(char c='a'; c<='z'; c++) {
        sc += (c == s[i]);
        tc += (c == t[i]);
        if(abs(sc - tc) <= match[i+1]) {
          ans.push_back(c);
          break;
        }
        sc -= (c == s[i]);
        tc -= (c == t[i]);
      }
    }
    cout << ans << nl;
  }

  return 0;
}
