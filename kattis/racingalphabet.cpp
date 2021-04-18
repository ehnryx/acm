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

int get(char c) {
  if(c == ' ') return 26;
  else if(c == '\'') return 27;
  else return c - 'A';
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

  const ld diam = 60;
  const ld circ = diam * M_PIl;
  const ld step = circ / 28 / 15;

  string line;
  getline(cin, line);
  int T = stoi(line);
  while(T--) {
    getline(cin, line);
    ld ans = size(line);
    for(int i=1; i<size(line); i++) {
      int d = abs(get(line[i-1]) - get(line[i]));
      if(d > 14) d = 28 - d;
      ans += d * step;
    }
    cout << ans << nl;
  }

  return 0;
}
