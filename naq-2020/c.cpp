//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  const int n = 8;
  vector grid(n, vector<char>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> grid[i][j];
    }
  }

  int cnt = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(grid[i][j] == '.') continue;

      cnt++;
      bool ok = true;
      for(int di=-1; di<=1; di++) {
        for(int dj=-1; dj<=1; dj++) {
          if(di == 0 && dj == 0) continue;
          for(int ii=i+di, jj=j+dj; 0<=ii && ii<n && 0<=jj && jj<n; ii+=di, jj+=dj) {
            ok &= (grid[ii][jj] == '.');
          }
        }
      }

      if(!ok) {
        cout << "invalid" << nl;
        return 0;
      }
    }
  }

  if(cnt == 8) {
    cout << "valid" << nl;
  } else {
    cout << "invalid" << nl;
  }

  return 0;
}
