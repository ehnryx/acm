#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

struct Point {
  ll x, y;
  Point(int x, int y): x(x), y(y) {}
  bool operator < (const Point& other) const {
    return x*other.y < y*other.x;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  ll x, y;
  int n;
  int a, b, h;

  cin >> x >> y;
  cin >> n;

  map<Point, int> idx[2];
  vector<vector<pair<ll, int>>> lines[2];
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> h;

    int side = 1;
    if (a < x || a == x && b < y) 
      side = 0;

    ll dist = (b-y)*(b-y) + (a-x)*(a-x);
    Point key(a-x, b-y);
    if (!idx[side].count(key)) {
      idx[side][key] = lines[side].size();
      lines[side].push_back({});
    }
    lines[side][idx[side][key]].push_back(pair<ll, int>(dist, h));
  }

  int ans = 0;
  int lis[n];
  for (int side = 0; side < 2; side++) {
    for (int i = 0; i < lines[side].size(); i++) {
      sort(lines[side][i].begin(), lines[side][i].end());
      int m = lines[side][i].size();
      memset(lis, INF, m*sizeof(lis[0]));
      for (int j = 0; j < m; j++) {
        int* it = lower_bound(lis, lis+m, lines[side][i][j].second);
        *it = lines[side][i][j].second;
      }
      ans += lower_bound(lis, lis+m, INF) - lis;
    }
  }
  cout << ans << nl;

  return 0;
}
