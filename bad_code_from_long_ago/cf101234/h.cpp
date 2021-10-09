#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ll> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

struct Point {
  int id;
  ll x, y;
  Point() {}
  Point(int i, ll x, ll y): id(i), x(x), y(y) {}
  bool operator < (const Point& other) const {
    return y * other.x < other.y * x;
  }
  bool operator == (const Point& other) const {
    return y * other.x == other.y * x;
  }
};
ostream& operator << (ostream& os, const Point& p) {
  return os << "(" << p.x << "," << p.y << ")";
}

int dir(const Point& a, const Point& b, const Point& c) {
  ll area = (a.x*b.y + b.x*c.y + c.x*a.y) - (a.y*b.x + b.y*c.x + c.y*a.x);
  return (area == 0) ? 0 : area/abs(area);
}

Point origin(-1,0,0);
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  int x, y;
  vector<Point> points, sorted;
  int pos = 0;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    if (pos >= 2 && points[pos-1] == points[pos-2] && Point(i,x,y) == points[pos-1]) {
      points[pos-1] = Point(pos-1,x,y);
      sorted[pos-1] = Point(pos-1,x,y);
    }
    else {
      points.push_back(Point(pos,x,y));
      sorted.push_back(Point(pos,x,y));
      pos++;
    }
  }
  if (points[0] == points[1] && points[0] == points[pos-1]) {
    if (points[pos-1] == points[pos-2]) {
      points[0] = points[pos-2];
      points[0].id = 0;
      points.pop_back();
      points.pop_back();
      sorted[0] = sorted[pos-2];
      sorted[0].id = 0;
      sorted.pop_back();
      sorted.pop_back();
    }
    else {
      points[0] = points[pos-1]; 
      points[0].id = 0;
      points.pop_back();
      sorted[0] = sorted[pos-1]; 
      sorted[0].id = 0;
      sorted.pop_back();
    }
  }
  sort(sorted.begin(), sorted.end());
  n = sorted.size();

  //cerr << "sorted: " << sorted << nl;

  int cur;
  int pref[n], suff[n];
  memset(pref, 0, sizeof pref);
  memset(suff, 0, sizeof suff);

  // forward
  cur = 1;
  for (int i = 0; i < n; ) {
    int last = i+1;
    while (last < n && sorted[i] == sorted[last]) {
      last++;
    }

    for (int j = i; j < last; j++) {
      int flag = 0;
      int a = dir(origin, points[(sorted[j].id)], points[(sorted[j].id+1)%n]);
      if (a == 0) {
        a = dir(origin, points[(sorted[j].id+1)%n], points[(sorted[j].id+2)%n]);
        flag = 1;
      }
      int b = dir(origin, points[(sorted[j].id)], points[(sorted[j].id+n-1)%n]);
      if (b == 0) {
        b = dir(origin, points[(sorted[j].id+n-1)%n], points[(sorted[j].id+n-2)%n]);
      }

      if (a < 0 && b < 0) {
        if (!flag && dir(sorted[j], points[(sorted[j].id+1)%n], points[(sorted[j].id+n-1)%n]) > 0)
          cur--;
      } else if (a > 0 && b > 0) {
        if (!flag && dir(sorted[j], points[(sorted[j].id+1)%n], points[(sorted[j].id+n-1)%n]) < 0)
          cur++;
      }
    }

    for (int j = i; j < last; j++) {
      pref[j] = cur;
    }

    i = last;
  }

  // reverse
  cur = -1;
  for (int i = n-1; i >= 0; ) {
    int last = i-1;
    while (last >= 0 && sorted[i] == sorted[last]) {
      last--;
    }

    for (int j = i; j > last; j--) {
      int flag = 0;
      int a = dir(origin, points[(sorted[j].id)], points[(sorted[j].id+1)%n]);
      if (a == 0) {
        a = dir(origin, points[(sorted[j].id+1)%n], points[(sorted[j].id+2)%n]);
        flag = 1;
      }
      int b = dir(origin, points[(sorted[j].id)], points[(sorted[j].id+n-1)%n]);
      if (b == 0) {
        b = dir(origin, points[(sorted[j].id+n-1)%n], points[(sorted[j].id+n-2)%n]);
      }

      if (a < 0 && b < 0) {
        if (!flag && dir(sorted[j], points[(sorted[j].id+1)%n], points[(sorted[j].id+n-1)%n]) < 0)
          cur--;
      } else if (a > 0 && b > 0) {
        if (!flag && dir(sorted[j], points[(sorted[j].id+1)%n], points[(sorted[j].id+n-1)%n]) > 0)
          cur++;
      }
    }

    for (int j = i; j > last; j--) {
      suff[j] = -cur;
    }

    i = last;
  }

  int ans = 2;
  for (int i = 0; i < n; i++) {
    //cerr << i << " --> " << sorted[i] << " : " << pt(pref[i], suff[i]) << nl;
    ans = max(ans, pref[i] + suff[i]);
  }
  cout << ans << nl;

  return 0;
}
