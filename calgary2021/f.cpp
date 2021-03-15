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

  int w, h, d;
  cin >> w >> h >> d;

  vector front(h, vector<char>(w));
  vector right(h, vector<char>(d));
  vector top(d, vector<char>(w));

  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
      cin >> front[i][j];
    }
  }

  for(int i=0; i<h; i++) {
    for(int j=0; j<d; j++) {
      cin >> right[i][j];
    }
  }

  for(int i=0; i<d; i++) {
    for(int j=0; j<w; j++) {
      cin >> top[d-1-i][j];
    }
  }

  int ans = 0;
  vector have(h, vector(w, vector<bool>(d)));
  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
      for(int k=0; k<d; k++) {
        if(front[i][j] == '#' && right[i][k] == '#' && top[k][j] == '#') {
          ans++;
          have[i][j][k] = true;
        }
      }
    }
  }

  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
      int cnt = 0;
      for(int k=0; k<d; k++) {
        cnt += have[i][j][k];
      }
      if(cnt == 0 && front[i][j] == '#') rip();
      if(cnt > 0 && front[i][j] == '.') rip();
    }
  }

  for(int i=0; i<h; i++) {
    for(int k=0; k<d; k++) {
      int cnt = 0;
      for(int j=0; j<w; j++) {
        cnt += have[i][j][k];
      }
      if(cnt == 0 && right[i][k] == '#') rip();
      if(cnt > 0 && right[i][k] == '.') rip();
    }
  }

  for(int k=0; k<d; k++) {
    for(int j=0; j<w; j++) {
      int cnt = 0;
      for(int i=0; i<h; i++) {
        cnt += have[i][j][k];
      }
      if(cnt == 0 && top[k][j] == '#') rip();
      if(cnt > 0 && top[k][j] == '.') rip();
    }
  }

  cout << ans << nl;

  return 0;
}
