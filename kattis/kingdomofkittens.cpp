#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
//%:include "utility/output.h"
%:include "geometry/convex_hull.h"
%:include "geometry/general.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  for(int n; cin >> n && n; ) {
    auto v = cin.read<point<ll>>(n);
    sort(begin(v), end(v));
    v.resize(unique(begin(v), end(v)) - begin(v));
    n = size(v); // wtf.......

    auto small = convex_hull(v);
    auto hull = convex_hull(v, true);

    if(size(small) <= 2) {
      cout << "YES" << nl;
      continue;
    }

    if(size(hull) != size(v)) {
      cout << "NO" << nl;
      continue;
    }

    if(size(small) <= 3) {
      cout << "YES" << nl;
      continue;
    }

    if(size(small) > 6) {
      cout << "NO" << nl;
      continue;
    }

    vector<int> idx;
    for(auto x : small) {
      idx.push_back(find(begin(hull), end(hull), x) - begin(hull));
    }
    int m = size(idx);
    vector<int> diff, big;
    for(int i=m-1, j=0; j<m; i=j++) {
      diff.push_back((idx[j] - idx[i] + n) % n);
      big.push_back(diff.back() > 1);
      assert(diff.back() >= 1);
    }

    function<bool(int, int)> check = [&](int i, int j) {
      if(i % 2 || j % 2) return true;
      i /= 2;
      j /= 2;
      int pi = (i + m-1) % m;
      int pj = (j + m-1) % m;
      return cross(small[i] - small[pi], small[j] - small[pj]) > 0;
    };

    bool ans = false;
    for(int i=0; i<2*m && !ans; i++) {
      for(int j=0; j<i && !ans; j++) {
        for(int k=0; k<j && !ans; k++) {
          // check
          bool ok = check(k, j) && check(j, i) && check(i, k);
          // check on_triangle
          for(int t=0; t<m && ok; t++) {
            // check edge
            if(big[t]) {
              ok &= (2*t == i || 2*t == j || 2*t == k);
            }
            // check vertex
            int nt = (2*t + 2) % (2 * m);
            ok &= (2*t == i || 2*t == j || 2*t == k ||
                nt == i || nt == j || nt == k ||
                2*t+1 == i || 2*t+1 == j || 2*t+1 == k);
          }
          ans |= ok;
        }
      }
    }

    cout << (ans ? "YES" : "NO") << nl;
  }

  return 0;
}
