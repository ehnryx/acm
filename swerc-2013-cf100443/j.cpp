#pragma GCC optimize("O3")
#pragma GCC target("sse2,sse4,tune=native")

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
typedef /*long*/ double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int M = 1.4e5;

template<class F>
ld quad(ld a, ld b, F f, const int n = M) {
	ld h = (b - a) / 2 / n, v = f(a) + f(b);
  for (int i = 1; i < n*2; i++)
		v += f(a + i*h) * (i&1 ? 4 : 2);
	return v * h / 3;
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

  int T;
  cin >> T;
  for(int tc=1; tc<=T; tc++) {
    cout << "Case " << tc << ": ";

    int n;
    cin >> n;
    vector<tuple<int,int,int,int>> circs;
    for(int i=0; i<n; i++) {
      int x, y, mid, rad;
      cin >> x >> y >> mid >> rad;
      int in = abs(mid - rad);
      int out = mid + rad;
      circs.emplace_back(x, y, in, out);
    }

    ld ans = quad(-1000, 1000, [=](ld x) {
      vector<pair<ld,ld>> segs;
      for(auto [cx, cy, in, out] : circs) {
        ld dx = abs(x - cx);
        if(dx >= out) continue;
        if(dx > in) {
          ld h = sqrt(out*out - dx*dx);
          segs.emplace_back(cy - h, cy + h);
        } else {
          ld h_out = sqrt(out*out - dx*dx);
          ld h_in = sqrt(in*in - dx*dx);
          segs.emplace_back(cy - h_out, cy - h_in);
          segs.emplace_back(cy + h_in, cy + h_out);
        }
      }
      sort(segs.begin(), segs.end());

      ld res = 0;
      ld top = -INF;
      for(auto [l, r] : segs) {
        if(top < l) {
          res += r - l;
          top = r;
        } else if(top < r) {
          res += r - top;
          top = r;
        }
      }
      return res;
    });

    cout << ans << nl;
  }

  return 0;
}
