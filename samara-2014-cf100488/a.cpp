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

const ld PI = acos((ld)-1);

ld heron(int a, int b, int c) {
  ld s = (ld)(a+b+c)/2;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

ld area(int a, int b, int c, int r) {
  ld ang = acos((ld)(b*b+c*c-a*a)/(2*b*c));
  ld arc = PI - ang;
  ld x = (ld)r / tan(ang/2);
  return x*r - (ld)r*r*arc/2;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(17);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int a, b, c, r;
  cin >> a >> b >> c >> r;
  ld tot = heron(a,b,c);
  ld safe = area(a,b,c,r) + area(b,c,a,r) + area(c,a,b,r);
  cout << (tot-safe)/tot << nl;

  return 0;
}
