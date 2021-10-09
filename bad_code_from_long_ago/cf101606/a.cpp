#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Place {
  int h, r, t;
  Place(int h, int r, int t):
    h(h), r(r), t(t) {}
  bool light(int i) const {
    int tt = t;
    if (tt < r) tt += h;
    i %= h;
    if (r < i && i < tt) return true;
    if (r < i+h && i+h < tt) return true;
    return false;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  vector<Place> places;

  int h, r, t;
  int lim = 0;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> h >> r >> t;
    lim = max(lim, h*1825);
    places.push_back(Place(h, r, t));
  }

  for (int i = 0; i < lim; i++) {
    bool good = true;
    for (const Place& p : places) {
      if (p.light(i))
        good = false;
    }
    if (good) {
      cout << i << nl;
      return 0;
    }
  }
  cout << "impossible" << nl;

  return 0;
}
