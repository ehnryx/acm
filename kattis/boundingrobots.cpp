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



//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int w, l;
  for (cin>>w>>l; w||l; cin>>w>>l) {
    --w; --l;
    int n;
    cin >> n;

    pt real(0,0);
    pt fake(0,0);
    char c; int d;
    for (int i=0; i<n; i++) {
      cin >> c >> d;
      if (c=='u') {
        fake += pt(0,d);
        real += pt(0,d);
        if (real.imag() > l) real = pt(real.real(), l);
      } else if (c=='d') {
        fake -= pt(0,d);
        real -= pt(0,d);
        if (real.imag() < 0) real = pt(real.real(), 0);
      } else if (c=='l') {
        fake -= pt(d,0);
        real -= pt(d,0);
        if (real.real() < 0) real = pt(0, real.imag());
      } else {
        fake += pt(d,0);
        real += pt(d,0);
        if (real.real() > w) real = pt(w, real.imag());
      }
    }

    cout << "Robot thinks " << llround(fake.real()) << " " << llround(fake.imag()) << nl;
    cout << "Actually at " << llround(real.real()) << " " << llround(real.imag()) << nl;
    cout << nl;
  }

  return 0;
}
