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

/* board:
 *         0
 *       1   2
 *     3   4   5
 *   6   7   8   9
 * 10  11  12  13  14
 */

const vector<tuple<int,int,int>> moves = {
  {0, 1, 3}, {1, 3, 6}, {3, 6, 10},
  {2, 4, 7}, {4, 7, 11},
  {5, 8, 12},
  {0, 2, 5}, {2, 5, 9}, {5, 9, 14},
  {1, 4, 8}, {4, 8, 13},
  {3, 7, 12},
  {3, 4, 5},
  {6, 7, 8}, {7, 8, 9},
  {10, 11, 12}, {11, 12, 13}, {12, 13, 14},
};

const int N = 15;
pair<char,char> board[N];

bool solve(int bm, pair<char,char> goal) {
  bool ok = false;
  for(int i=0; i<N; i++) {
    if(bm & 1<<i) {
      ok |= (board[i] == goal);
    }
  }
  if(!ok) return false;
  if(__builtin_popcount(bm) == 1) return true;

  for(auto [a, b, c] : moves) {
    for(int t=0; t<2; t++, swap(a, c)) {
      if((bm & 1<<a) && (bm & 1<<b) && !(bm & 1<<c)) {
        swap(board[a], board[c]);
        if(solve(bm ^ 1<<a ^ 1<<b ^ 1<<c, goal)) return true;
        swap(board[a], board[c]);
      }
    }
  }
  return false;
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

  for(pair<char,char> goal; cin >> goal.first >> goal.second && goal.first != '*'; ) {
    int bm = 0;
    for(int i=0; i<15; i++) {
      cin >> board[i].first >> board[i].second;
      if(isalpha(board[i].first)) bm |= 1 << i;
    }
    if(solve(bm, goal)) {
      cout << "Possible" << nl;
    } else {
      cout << "Impossible" << nl;
    }
  }

  return 0;
}
