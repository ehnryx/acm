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
  Point(const pii& p, ll v): x(p.first), y(p.second), v(v) {}
  bool operator < (const Point& v) const {
    if (x == v.x) return y > v.y;
    else return x < v.x;
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

  int n, a, b, c;
  cin >> n;

  map<pii,ll> p;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> c;
    p[pii(a,b)] += c;
  }

  vector<Point> arr;
  for (const auto& it : p) {
    arr.push_back(Point(it.first, it.second));
  }
  n = arr.size();
  sort(arr.begin(), arr.end());

  map<ll,ll> lis;
  for (int i=0; i<n; i++) {
    auto it = lis.lower_bound(arr[i].y);
    ll cur = arr[i].v;
    while (cur > 0 && it != lis.end()) {
      if (it->second <= cur) {
        cur -= it->second;
        it = lis.erase(it);
      }
      else {
        it->second -= cur;
        cur = 0;
      }
    }
    lis[arr[i].y] += arr[i].v;
  }

  ll ans = 0;
  for (const auto& it : lis) {
    ans += it.second;
  }
  cout << ans << nl;

  return 0;
}
