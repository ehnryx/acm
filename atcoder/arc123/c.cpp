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

bool solve(const string& s, int have) {
  for(char c : s) {
    while (have > 0 && !(have <= c-'0' && c-'0' <= 3*have)) {
      have--;
    }
    if(have == 0) return false;
  }
  return true;
}

bool solve_four(const string& s, int have = 4) {
  int carry = 0;
  for (char c : s) {
    if (have == 4) {
      int d = c - '0' - carry;
      if (d < 4) {
        if (d == 3) {
          have = 3;
        }
        carry = 1;
      } else {
        carry = 0;
      }
    } else {
      while (have > 0 && !(have <= c-'0' && c-'0' <= 3*have)) {
        have--;
      }
      if(have == 0) return false;
    }
  }
  return true;
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
    string s;
    cin >> s;
    reverse(begin(s), end(s));
    if (solve(s, 1)) {
      cout << 1 << nl;
    } else if (solve(s, 2)) {
      cout << 2 << nl;
    } else if (solve(s, 3)) {
      cout << 3 << nl;
    } else if (solve_four(s)) {
      cout << 4 << nl;
    } else {
      cout << 5 << nl;
    }
  }

  return 0;
}

// 123
//  23456
//   3456789k
