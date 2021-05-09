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

int add(int a, int b, int m) {
  a += b;
  while(a > m+1) a -= m;
  return a;
}

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
  while(T--) {
    int n, m;
    cin >> n >> m;
    vector<string> s(m);
    for(int i=0; i<m; i++) {
      char _;
      cin >> _ >> s[i];
    }
    string t;
    cin >> t;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i=1; i<=n; i++) {
      for(const string& pat : s) {
        if(size(pat) > i) continue;
        int start = i - size(pat);
        if(t.substr(start, size(pat)) != pat) continue;
        dp[i] = add(dp[i], dp[start], 128);
      }
    }
    if(dp[n] == 0) {
      cout << "nonono" << nl;
    } else if(dp[n] == 1) {
      cout << "happymorsecode" << nl;
    } else {
      cout << "puppymousecat" << " " << dp[n] % 128 << nl;
    }
  }

  return 0;
}
