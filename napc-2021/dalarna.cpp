#pragma GCC optimize("O3,fast-math")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr ld EPS = 1e-12L;
random_device _rd; mt19937 rng(_rd());

constexpr ld PI = M_PIl;

ld cp(const pt& a, const pt& b) { return imag(conj(a) * b); }
ld dp(const pt& a, const pt& b) { return real(conj(a) * b); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a);
}
bool parallel(const pt& a, const pt& b, const pt& c, const pt& d) {
  return abs(cp(a-b, c-d) / abs(a-b)) < EPS;
}
bool on_segment(const pt& c, const pt& a, const pt& b) {
  if (!parallel(a, c, b, c)) return false;
  return abs(c-a) < EPS || abs(c-b) < EPS || (dp(c-a, b-a) > 0 && dp(c-b, a-b) > 0);
}

ld area(const vector<pt>& v) {
  int n = v.size();
  ld ans = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    ans += cp(v[i], v[j]);
  }
  return ans / 2;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int guesses = (argc > 1 ? atoi(argv[1]) : 1'000'000);
  cerr << "guess " << guesses << " angles" << nl;

  const pt rotation = polar((ld)1, (ld)1.789); // VIVE LA REVOLUTION

  int n, k, x, y;
  cin >> n >> k >> x >> y;
  pt start = pt(x, y) * rotation;

  vector<pt> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.push_back(pt(a, b) * rotation);
  }
  if (area(v) < 0) {
    reverse(begin(v), end(v));
  }

  vector<ld> left(n, numeric_limits<ld>::max()), right(n);
  for(int bs=0; bs<guesses; bs++) {
    pt cur = start;
    pt dir = polar((ld)1, 2 * PI * bs / guesses);
    for(int bounce=0; bounce<=k; bounce++) {
      pair<ld, int> closest(numeric_limits<ld>::max(), -1);
      //cerr << "guess " << bs << " start " << cur << " with dir " << dir << nl;
      for(int i=n-1, j=0; j<n; i=j++) {
        //cerr << "try " << v[i] << " " << v[j] << " with " << cur << nl;
        if(on_segment(cur, v[i], v[j])) continue;
        //cerr << "not on segment " << cur << nl;
        if(parallel(0, dir, v[i], v[j])) continue;
        pt it = line_inter(cur, cur + dir, v[i], v[j]);
        //cerr << "ok, continue, it with " << v[i] << " " << v[j] << " :: " << it << nl;
        if(dp(it - cur, dir) < 0 || !on_segment(it, v[i], v[j])) continue;
        closest = min(closest, pair(abs(it - cur), i));
      }
      assert(closest.second != -1);
      int i = closest.second;
      int j = (i + 1 < n ? i + 1 : 0);
      pt it = line_inter(cur, cur + dir, v[i], v[j]);
      pt mid = line_inter(cur, cur + (v[j] - v[i]), it, it + (v[j] - v[i]) * pt(0, 1));
      dir = (mid + mid - cur) - it;
      dir /= abs(dir);
      cur = it;

      ld dist = abs(cur - v[i]);
      left[i] = min(left[i], dist);
      right[i] = max(right[i], dist);
    }
  }

  ld ans = 0;
  for(int i=0; i<n; i++) {
    cerr << i << " -> " << v[i] << " " << v[(i+1)%n] << " get " << left[i] << " -- " << right[i] << nl;
    if(left[i] <= right[i]) {
      ans += right[i] - left[i];
    }
  }
  cout << ans << nl;

  return 0;
}
