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

void rip() {
  cout << "invalid" << nl;
  exit(0);
}

const int N = 10;
char region[N][N];
char grid[N][N];

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

  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      cin >> region[i][j];
    }
  }

  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      cin >> grid[i][j];
    }
  }

  vector<int> regcnt(N), rowcnt(N), colcnt(N);
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      if(grid[i][j] == '*') {
        rowcnt[i]++;
        colcnt[j]++;
        regcnt[region[i][j] - '0']++;
        int cell = 0;
        for(int di=-1; di<=1; di++) {
          for(int dj=-1; dj<=1; dj++) {
            if(i+di < 0 || j+dj < 0 || i+di >= N || j+dj >= N) continue;
            cell += (grid[i+di][j+dj] == '*');
          }
        }
        if(cell > 1) rip();
      }
    }
  }

  if(*min_element(regcnt.begin(), regcnt.end()) != 2) rip();
  if(*min_element(rowcnt.begin(), rowcnt.end()) != 2) rip();
  if(*min_element(colcnt.begin(), colcnt.end()) != 2) rip();
  cout << "valid" << nl;

  return 0;
}
