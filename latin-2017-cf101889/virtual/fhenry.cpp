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

struct Point {
  int x, y; ll v;
  Point(int x, int y, ll v): x(x), y(y), v(v) {}
  bool operator < (const Point& v) const {
    if (x != v.x) return x < v.x;
    else return y > v.y;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n, a, b, v;
  cin >> n;

  map<pii,ll> combine;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> v;
    combine[pii(a,b)] += v;
  }

  vector<Point> p;
  for (const auto& it : combine) {
    p.push_back(Point(it.first.first,it.first.second,it.second));
  }
  sort(p.begin(), p.end());

  map<ll,ll> lis;
  for (int i=0; i<(int)p.size(); i++) {
    auto it = lis.lower_bound(p[i].y);
    ll cur = p[i].v;
    while (cur > 0 && it != lis.end()) {
      if (it->second <= cur) {
        cur -= it->second;
        it = lis.erase(it);
      }
      else {
        it->second -= cur;
        break;
      }
    }
    lis[p[i].y] += p[i].v;
  }

  ll ans = 0;
  for (const auto& it : lis) {
    ans += it.second;
  }
  cout << ans << nl;

  return 0;
}
