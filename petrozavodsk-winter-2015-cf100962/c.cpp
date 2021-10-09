#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953L;

struct Point {
  ld x;
  int v;
  Point(){}
  Point(ld x, int v): x(x), v(v) {}
  bool operator < (const Point& p) const {
    if (abs(x-p.x) < EPS) return v > p.v;
    else return x < p.x;
  }
};

ld sqr(const ld& x) { return x*x; }
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld sgn(const ld& x) { return (abs(x)<EPS ? 0 : (x<0 ? -1 : 1)); }
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

const ld radius = 1e9-1;

ld get_p(const pt& x, ld ang) {
  pt dir = exp(pt(0,ang));
  pt base = line_inter(x, x+dir, 0, pt(0,1)*dir);
  ld len = sqrt(sqr(radius) - sqr(abs(base)));
  pt circ = base + len*dir;
  ld res = arg(circ);
  if (res < 0) res += 2*PI;
  return res;
}

pdd intersect(const pt& x, ld ang, ld rot) {
  return pdd(get_p(x, rot), get_p(x, rot+ang));
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  vector<Point> p;
  int a, b, ang, rot;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> ang >> rot;

    pdd seg = intersect(pt(a,b), PI/180 * ang/3600, PI/180 * rot/3600);
    if (seg.first < EPS) seg.first += 2*PI;
    p.push_back(Point(seg.first, 1));
    p.push_back(Point(seg.second, -1));
    if (seg.first > seg.second) {
      p.push_back(Point(-PI, 1));
      p.push_back(Point(3*PI, -1));
    }
  }
  p.push_back(Point(0, 0));
  sort(p.begin(), p.end());

  for (;;) {
    int cnt = 0;
    for (const Point& it : p) {
      cnt += it.v;
      assert(cnt >= 0);
      if (cnt == 0 && -1 < it.x && it.x < 2*PI + 1 && rng()%7 == 0) {
        cout << "YES" << nl;
        pt approx = radius * exp(pt(0,it.x+2e-9));
        cout << llround(approx.real()) << " " << llround(approx.imag()) << nl;
        return 0;
      }
    }
  }

  assert(false);
  cout << "rm -rf /" << nl;

  return 0;
}
