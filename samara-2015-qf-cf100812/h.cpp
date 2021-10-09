#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld lp_dist(const pt& a, const pt& b, const pt& p) {
  return cp(b-a, p-a) / abs(b-a);
}
pt normalize(const pt& v) { return v / abs(v); }
ld sqr(const ld& x) { return x*x; }

ld circ(const ld& r, const pt& a, const pt& b, pt& c) {
  if (a == pt(0,0)) return 0;
  pt d = normalize(-a);
  ld radius = (r + abs(a)) / 2;
  c = a + radius*d;
  if (abs(b-c) < radius) return 0;
  else return radius;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int r, x, y;
  pt a, b;

  cin >> r;
  cin >> x >> y;
  a = pt(x,y);
  cin >> x >> y;
  b = pt(x,y);

  pt o(0,0);

  pt n = normalize((b-a)*pt(0,1));
  if (lp_dist(a, b, o) < 0) {
    n = -n;
  }

  pt center;
  pt m = (ld)0.5 * (a+b);
  ld half = abs(m-a);
  ld left, right, mid;
  left = half;
  right = r;
  while (right - left > EPS) {
    mid = (left + right) / 2;
    ld leg = sqrt(sqr(mid) - sqr(half));
    center = m + leg*n;
    pt far = center + mid*normalize(center);
    (abs(far) < r ? left : right) = mid;
  }

  //cerr << "first round: " << mid << " " << center << nl;

  pt tempc;
  ld cur;

  cur = circ(r, a, b, tempc);
  if (cur > mid) {
    mid = cur;
    center = tempc;
  }
  cur = circ(r, b, a, tempc);
  if (cur > mid) {
    mid = cur;
    center = tempc;
  }

  cout << mid << nl;
  cout << center.real() << " " << center.imag() << nl;

  return 0;
}
