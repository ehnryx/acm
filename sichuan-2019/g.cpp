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

void solve() {
  static const int N = 1e6 + 1;
  static vector<bool> np(N);
  for(static int i=2; i*i<N; i++) {
    if(np[i]) continue;
    for(int j=i*i; j<N; j+=i) {
      np[j] = true;
    }
  }

  function<bool(int,int,int)> equal = [=](int x, int y, int k) {
    while(x>k && y>k) {
      if(!np[x] && !np[y]) {
        return true;
      }
      x--;
      y--;
    }
    return false;
  };

  int x, y, k, w;
  cin >> x >> y >> k >> w;
  if(x == k || y == k) {
    cout << "Bob" << nl;
  } else if(!np[x] && !np[y]) {
    cout << "Alice" << nl;
  } else if(w) {
    if(equal(x, y, k)) {
      cout << "Alice" << nl;
    } else {
      cout << "Bob" << nl;
    }
  } else {
    if(equal(x-1, y, k) || equal(x, y-1, k)) {
      cout << "Alice" << nl;
    } else {
      cout << "Bob" << nl;
    }
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

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ": ";
    solve();
  }

  return 0;
}
