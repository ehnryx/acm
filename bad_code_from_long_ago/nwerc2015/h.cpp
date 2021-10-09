#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll __int128
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct Rational {
  ll a, b;
  Rational(){}
  Rational(ll a, ll b) {
    this->a = a;
    this->b = b;
  }
  bool operator < (const Rational& other) const {
    return a*other.b < b*other.a;
  }
  bool operator == (const Rational& other) const {
    return a*other.b == b*other.a;
  }
  bool operator == (const ll& other) const {
    return a == b*other;
  }
};

struct Point {
  ll x, y;
  Point(){}
  Point(ll x, ll y) {
    this->x = x;
    this->y = y;
  }
  Point scale(ll f) {
    return Point(x*f, y*f);
  }
  bool operator < (const Point& other) const {
    return (x < other.x || y < other.y);
  }
};
struct Wall {
  Point a, b;
  Wall(){}
  Wall(const Point& a, const Point& b) {
    if (a < b) {
      this->a = a;
      this->b = b;
    } else {
      this->a = b;
      this->b = a;
    }
  }
  Wall scale(ll f) {
    return Wall(a.scale(f), b.scale(f));
  }
  bool contains(Point h, bool strict) {
    if (vert()) {
      Wall range = this->scale(h.x);
      Point im = h.scale(a.x);
      if (strict) return range.a.y < im.y && im.y < range.b.y;
      else return (range.a.y <= im.y && im.y <= range.b.y);
    } else {
      Wall range = this->scale(h.y);
      Point im = h.scale(a.y);
      if (strict) return (range.a.x < im.x && im.x < range.b.x);
      else return (range.a.x <= im.x && im.x <= range.b.x);
    }
  }
  void fix() {
    if (b < a) {
      Point t = a;
      a = b;
      b = t;
    }
  }
  bool vert() const {
    return a.x == b.x;
  }
};

struct Field {
  Point hole;
  Point imhole;
  vector<Wall> walls;
  vector<Wall> reflected[9];
  Rational dist[9][9];
  int n;
  Field(int n) {
    this->n = n;
  }
  void add_hole(const Point& p) {
    hole = p;
  }
  void add_wall(const Point& a, const Point& b) {
    walls.push_back(Wall(a, b));
  }

  bool verify(const vector<int>& perm) {
    imhole = hole;
    int cnt = 0;
    reflected[cnt++] = walls;
    for (int curr: perm) {
      reflected[cnt].resize(n);
      for (int i = 0; i < n; i++) {
        reflected[cnt][i].a = reflect(reflected[cnt-1][i].a, reflected[cnt-1][curr]);
        reflected[cnt][i].b = reflect(reflected[cnt-1][i].b, reflected[cnt-1][curr]);
        reflected[cnt][i].fix();
      }
      imhole = reflect(imhole, reflected[cnt-1][curr]);
      cnt++;
    }
    // verify
    Rational maxdist[10];
    for (int t = 0; t <= perm.size(); t++) {
      for (int i = 0; i < n; i++) {
        if (t < perm.size() && i == perm[t]) {
          if (reflected[t][i].vert()) {
            if (reflected[t][i].contains(imhole, false)) {
              dist[t][i] = Rational((imhole.x*reflected[t][i].a.x)*(imhole.x*reflected[t][i].a.x) + (imhole.y*reflected[t][i].a.x)*(imhole.y*reflected[t][i].a.x), (imhole.x)*(imhole.x));
            } else { 
              dist[t][i] = Rational(-1,1);
            }
          } else {
            if (reflected[t][i].contains(imhole, false)) {
              dist[t][i] = Rational((imhole.y*reflected[t][i].a.y)*(imhole.y*reflected[t][i].a.y) + (imhole.x*reflected[t][i].a.y)*(imhole.x*reflected[t][i].a.y), (imhole.y)*(imhole.y));
            } else { 
              dist[t][i] = Rational(-1,1);
            }
          }
        } else {
          if (reflected[t][i].vert()) {
            if (reflected[t][i].contains(imhole, true)) {
              dist[t][i] = Rational((imhole.x*reflected[t][i].a.x)*(imhole.x*reflected[t][i].a.x) + (imhole.y*reflected[t][i].a.x)*(imhole.y*reflected[t][i].a.x), (imhole.x)*(imhole.x));
            } else { 
              dist[t][i] = Rational(-1,1);
            }
          } else {
            if (reflected[t][i].contains(imhole, true)) {
              dist[t][i] = Rational((imhole.y*reflected[t][i].a.y)*(imhole.y*reflected[t][i].a.y) + (imhole.x*reflected[t][i].a.y)*(imhole.x*reflected[t][i].a.y), (imhole.y)*(imhole.y));
            } else { 
              dist[t][i] = Rational(-1,1);
            }
          }
        }
      }
      if (t == 0) maxdist[t] = Rational(0,1);
      else maxdist[t] = dist[t-1][perm[t-1]];
    } 
    maxdist[perm.size()+1] = Rational(imhole.x*imhole.x + imhole.y*imhole.y, 1);

#ifdef DEBUG
    cout << endl;
    cout << "perm: ";
    for (int id: perm) cout << id << " ";
    cout << endl;
    cout << "imhole: " << imhole.x << " " << imhole.y << endl;
    cout << "maxdist: ";
    for (int i = 0; i <= perm.size()+1; i++)
      cout << maxdist[i].a << "," << maxdist[i].b << " ";
    cout << endl;
    for (int t = 0; t <= perm.size(); t++) {
      cout << "time " << t << nl;
      for (int i = 0; i < n; i++) {
        cout << reflected[t][i].a.x << " " << reflected[t][i].a.y << " " << reflected[t][i].b.x << " " << reflected[t][i].b.y << ": " << dist[t][i].a << "," << dist[t][i].b << endl;
      }
    }
#endif

    vector<bool> hit(n);
    for (int t = 0; t <= perm.size(); t++) {
      if (t < perm.size())
        hit[perm[t]] = true;
      //cerr << "time: " << t << nl;
      if (maxdist[t] == -1) return false;
      for (int i = 0; i < n; i++) {
        //cerr << i << ": " << maxdist[t] << " < " << dist[t][i] << " < " << maxdist[t+1] << nl;
        if (!hit[i] && maxdist[t] < dist[t][i] && dist[t][i] < maxdist[t+1]) {
          return false;
        }
      }
    }
    for (int i = 1; i <= perm.size()+1; i++) {
      if (maxdist[i] < maxdist[i-1]) 
        return false;
    }
    return true;
  }
  Point reflect(const Point& p, const Wall& mid) {
    if (mid.vert()) return Point(p.x + 2*(mid.a.x - p.x), p.y);
    else return Point(p.x, p.y + 2*(mid.a.y - p.y));
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, a, b, x, y;
  cin >> n;
  Field field(n);
  cin >> x >> y;
  field.add_hole(Point(x,y));
  for (int i = 0; i < n; i++) {
    cin >> a >> b >> x >> y;
    field.add_wall(Point(a,b), Point(x,y));
  }

  vector<int> combinations[n+1];
  for (int bm = 0; bm < (1<<n); bm++) {
    combinations[__builtin_popcount(bm)].push_back(bm);
  }
  for (int len = n; len >= 0; len--) {
    for (int bm: combinations[len]) {
      vector<int> perm;
      for (int i = 0; i < n; i++) {
        if ((1<<i) & bm)
          perm.push_back(i);
      }
      do {
        if (field.verify(perm)) {
          cout << len << nl;
          return 0;
        }
      } while (next_permutation(perm.begin(), perm.end()));
    }
  }

  cout << "impossible" << nl;
  return 0;
}

