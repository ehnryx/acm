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

/* 0 1 2
 * 3 4 5
 * 6 7 8
 */
const vector<tuple<int,int,int>> rows = {
  {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
  {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
  {0, 4, 8}, {2, 4, 6},
};

bool has_row(int bm) {
  for(auto [a, b, c] : rows) {
    int va = bm >> (2*a) & 0b11;
    int vb = bm >> (2*b) & 0b11;
    int vc = bm >> (2*c) & 0b11;
    if(va && va == vb && vb == vc) {
      return true;
    }
  }
  return false;
}

const int N = 3;
const int M = 1 << (2 * N * N);
int ans[M];
void generate(int bm) {
  if(__builtin_popcount(bm) == 9 || has_row(bm)) {
    ans[bm] = 1;
    return;
  }
  ans[bm] = 2;
  int put = 1 << (__builtin_popcount(bm) % 2);
  for(int i=0; i<9; i++) {
    if(bm & 0b11 << (2*i)) continue;
    generate(bm | put << (2*i));
  }
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

  fill(begin(ans), end(ans), 3);
  generate(0);

  int T;
  cin >> T;
  while(T--) {
    int bm = 0;
    for(int i=0; i<9; i++) {
      char c;
      cin >> c;
      if(c == 'X') {
        bm = bm << 2 | 0b01;
      } else if(c == 'O') {
        bm = bm << 2 | 0b10;
      } else {
        bm = bm << 2;
      }
    }
    cout << ans[bm] << nl;
  }

  return 0;
}
