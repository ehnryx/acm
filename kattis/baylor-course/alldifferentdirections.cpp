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

  for (int n;;) {
    cin >> n;
    if (!n) break;

    pt avg = 0;
    vector<pt> p;

    string s;
    getline(cin, s);
    for (int i=0; i<n; i++) {
      getline(cin, s);
      istringstream ss(s);
      ld x, y, a;
      ss >> x >> y >> s >> a;
      pt pos(x,y);
      pt dir(exp(pt(0,M_PIl*a/180)));
      while (ss >> s >> a) {
        if (s == "walk") {
          pos += a*dir;
        } else {
          dir *= exp(pt(0,M_PIl*a/180));
        }
      }
      avg += pos/(ld)n;
      p.push_back(pos);
    }

    int worst = 0;
    for (int i=1; i<n; i++) {
      if (abs(p[i]-avg) > abs(p[worst]-avg)) {
        worst = i;
      }
    }
    cout << avg.real() << " " << avg.imag() << " " << abs(p[worst]-avg) << nl;
  }

  return 0;
}
