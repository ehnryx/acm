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
typedef double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

template<class F>
ld quad(ld a, ld b, F f, const int n = 10000) {
	ld h = (b - a) / 2 / n, v = f(a) + f(b);
  for (int i = 1; i < n*2; i++)
		v += f(a + i*h) * (i&1 ? 4 : 2);
	return v * h / 3;
}

const ld PI = acos((ld)-1);

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
  while(T--) {
    int a, b;
    cin >> a >> b;
    ld half = 2*b/PI * quad(0, 2*a, [=](const ld& x) {
      return PI - acos((x - a) / a);
    });
    cout << 2 * half + PI*a*a << nl;
  }

  return 0;
}
