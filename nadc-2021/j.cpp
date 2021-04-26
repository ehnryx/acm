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
random_device _rd; mt19937 rng(_rd());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
ld area(const vector<pt>& v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]);
  return abs(s)/2;
}

ld rectangle(const pt& a, const pt& b) {
  return abs(a.real() - b.real()) * abs(a.imag() - b.imag());
}

ld solve(const pt& c, const pt& b, const pt& x, const pt& y) {
  ld ans = 2 * rectangle(c, b) / 3;
  //cerr << ans << " " << c << " " << b << nl;
  if(!(dp(y - x, b - x) > 0 && dp(x - y, b - y) > 0)) {
    //cerr << " ?? " << nl;
    ld xy = abs(x - y);
    if(x.real() == y.real()) xy -= abs(c.imag() - x.imag());
    else xy -= abs(c.real() - x.real());
    ld height = (x.real() == y.real() ? abs(x.real() - c.real()) : abs(x.imag() - c.imag()));
    ld by = abs(b - y);
    ld r = (xy + by) / (height*height);
    ld h = sqrt(by / r);
    ans -= 2 * h * by / 3;
  }
  return ans;
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

  int n;
  cin >> n;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    v.emplace_back(x, y);
  }

  if(n < 6) {
    cout << area(v) << nl;
    return 0;
  }

  int c = -1;
  for(int i=0; i<n; i++) {
    int pi = (i + n-1) % n;
    int ni = (i + 1) % n;
    if(cp(v[ni] - v[i], v[i] - v[pi]) > 0) {
      c = i;
    }
  }

  int o = (c + 3) % 6;
  ld ans = rectangle(v[c], v[o]);
  //cerr << "rect " << ans << nl;

  {
    //pt s = v[(c + 1) % 6];
    pt t = v[(c + 2) % 6];
    pt x = v[(c + 3) % 6];
    pt y = v[(c + 4) % 6];
    pt b = line_inter(t, v[c], x, y);
    ans += solve(v[c], b, x, y);
  }

  {
    //pt s = v[(c + 5) % 6];
    pt t = v[(c + 4) % 6];
    pt x = v[(c + 3) % 6];
    pt y = v[(c + 2) % 6];
    pt b = line_inter(t, v[c], x, y);
    ans += solve(v[c], b, x, y);
  }

  cout << ans << nl;

  return 0;
}
