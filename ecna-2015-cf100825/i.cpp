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

  int n;
  cin >> n;
  char g[n][n];
  int cnt = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
      cnt += (g[i][j] == '.');
    }
  }
  string s;
  cin >> s;
  int sid = 0;

  if(cnt * 4 != n*n) {
    cout << "invalid grille" << nl;
    return 0;
  }

  char res[n][n];
  memset(res, 0, sizeof res);
  for(int rot=0; rot<4; rot++) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(g[i][j] == '.') {
          if(res[i][j]) {
            cout << "invalid grille" << nl;
            return 0;
          }
          res[i][j] = s[sid++];
        }
      }
    }
    char nxt[n][n];
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        nxt[i][j] = g[n-1-j][i];
      }
    }
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        g[i][j] = nxt[i][j];
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cout << res[i][j];
    }
  }
  cout << nl;

  return 0;
}
