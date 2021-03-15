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

  int n, m;
  cin >> n >> m;
  vector<pair<int,int>> up, down;
  int total = 0;
  for(int i=0; i<n; i++) {
    int h, t;
    cin >> h >> t;
    up.emplace_back(h, t);
    total += h;
  }
  for(int i=0; i<m; i++) {
    int h, t;
    cin >> h >> t;
    down.emplace_back(h, t);
  }

  ld l = 0;
  ld r = 500000;
  for(int bs=0; bs<100; bs++) {
    ld v = (l+r) / 2;
    ld uval = 0, ut = 0;
    for(int i=0; i<n; i++) {
      if(ut + up[i].second < v) {
        ut += up[i].second;
        uval += up[i].first;
      } else {
        uval += (v - ut) / up[i].second * up[i].first;
        break;
      }
    }
    ld dval = total, dt = 0;
    for(int i=0; i<m; i++) {
      if(dt + down[i].second < v) {
        dt += down[i].second;
        dval -= down[i].first;
      } else {
        dval -= (v - dt) / down[i].second * down[i].first;
        break;
      }
    }
    if(uval >= dval - EPS) {
      r = v;
    } else {
      l = v;
    }
  }
  cout << r << nl;

  return 0;
}
