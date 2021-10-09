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

ll weighted_lis_len(const vector<pair<int,ll>>& a) {
    int n = a.size();
    map<int,ll> lis;
    for (int i = 0; i < n; i++) {
        auto it = lis.lower_bound(a[i].first);
        ll cur = a[i].second;
        while (cur > 0 && it != lis.end()) {
            if (it->second <= cur) {
                cur -= it->second;
                it = lis.erase(it);
            } else {
                it->second -= cur;
                cur = 0;
            }
        }
        lis[a[i].first] += a[i].second;
    }
    ll len = 0;
    for (const auto& it : lis) {
        len += it.second;
    }
    return len;
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

  vector<pair<int,ll>> lis;
  for (const Point& it : arr) {
    lis.push_back(pair<int,ll>(it.y, it.v));
  }
  cout << weighted_lis_len(lis) << nl;

  return 0;
}
