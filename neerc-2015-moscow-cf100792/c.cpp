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

const int M = 1e9;

bool query_x(int x) {
  assert(x < M);
  int radius = min(x+1, M-x);
  int l = x - radius + 1;
  int r = x + radius;
  assert(0 <= l && l < r && r <= M);

  int right;
  cout << l << " " << 0 << endl;
  cin >> right;
  cout << r << " " << 0 << endl;
  cin >> right;
  if(right) {
    return false;
  } else {
    return true;
  }
}

bool query_y(int x) {
  assert(x < M);
  int radius = min(x+1, M-x);
  int l = x - radius + 1;
  int r = x + radius;
  assert(0 <= l && l < r && r <= M);

  int right;
  cout << 0 << " " << l << endl;
  cin >> right;
  cout << 0 << " " << r << endl;
  cin >> right;
  if(right) {
    return false;
  } else {
    return true;
  }
}

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

  int x = -1, y = -1;

  {
    int l = 0;
    int r = M;
    while(l < r) {
      int m = (l+r) / 2;
      if(query_x(m)) {
        r = m;
      } else {
        l = m+1;
      }
    }
    x = r;
  }

  {
    int l = 0;
    int r = M;
    while(l < r) {
      int m = (l+r) / 2;
      if(query_y(m)) {
        r = m;
      } else {
        l = m+1;
      }
    }
    y = r;
  }

  cout << "A " << x << " " << y << endl;

  return 0;
}
