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

template <class T, bool lin=true, bool rin=false>
struct IntervalSet {
  T inf;
    set<pair<T,T>> s;
  IntervalSet(T inf): inf(inf) {}
    bool cmp(T a, T b, bool l, bool r=false) {
        if (l||r) return a < b || a == b;
        else return a < b;
    }
    void insert(T a, T b) {
        if (s.empty()) { s.insert({a,b}); return; }
        auto it = s.upper_bound({a,inf});
        while (it != s.end() && cmp(it->first,b,lin,rin)) {
            b = max(b, it->second);
            it = s.erase(it);
        }
    it = s.upper_bound({a,inf});
    while (it != s.begin() && cmp(a,(--it)->second,lin,rin)) {
      a = min(a, it->first);
      b = max(b, it->second);
      it = s.erase(it);
    }
    s.insert({a,b});
    }
    pair<T,T> find(T x) {
        if (s.empty()) { return {inf,inf}; }
        auto it = s.upper_bound({x,inf});
        if (it == s.begin()) return {inf,inf};
        if (cmp((--it)->second,x,!rin)) return {inf,inf};
        if (cmp(x,it->first,!lin)) return {inf,inf};
        return *it;
    }
};

struct Point {
  ll x, y;
  Point(int x, int y): x(x), y(y) {}
  ll operator * (const Point& v) const {
    return x*v.y - y*v.x;
  }
  Point operator - (const Point& v) const {
    return Point(x-v.x, y-v.y);
  }
  Point operator + (const Point& v) const {
    return Point(x*v.x-y*v.y, x*v.y+y*v.x);
  }
};

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    if (b) {
      ll g = __gcd(a,b);
      n = a/g; d = b/g;
      if (d<0) { n = -n; d = -d; }
    } else {
      n = (a ? a/abs(a) : 0);
      d = 0;
    }
  }
  bool operator < (const Frac& f) const {
    return n*f.d < d*f.n;
  }
  bool operator == (const Frac& f) const {
    return n==f.n && d==f.d;
  }
  friend ostream& operator << (ostream& os, const Frac& f) {
    return os << f.n << '/' << f.d;
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

  int n, q, x, y;
  cin >> n >> q;

  vector<Point> p;
  for (int i=0; i<n; i++) {
    cin >> x >> y;
    p.push_back(Point(x,y));
  }

  IntervalSet<Frac,false> iset(Frac(1,0));
  bool inf = false;

  for (int i=0; i<n; i++) {
    int pre = (i-1<0 ? n-1 : i-1);
    int nxt = (i+1<n ? i+1 : 0);
    if ((p[i]-p[pre]) * (p[nxt]-p[i]) < 0) {
      Point first = (p[i]-p[pre])+Point(0,-1);
      Point second = (p[nxt]-p[i])+Point(0,-1);
      Frac left = Frac(second.y,second.x);
      Frac right = Frac(first.y,first.x);
      if (right < left) {
        inf = true;
        iset.insert(left,Frac(1,0));
        iset.insert(Frac(-1,0),right);
      }
      else {
        iset.insert(left,right);
      }
    }
  }

  auto query = [&] (Frac f) {
    if (f == Frac(1,0) || f == Frac(-1,0)) return inf;
    return !(iset.find(f) == pair<Frac,Frac>(Frac(1,0),Frac(1,0)));
  };

  for (int i=0; i<q; i++) {
    cin >> x >> y;
    if (query(Frac(y,x))) {
      cout << "N" << nl;
    } else {
      cout << "Y" << nl;
    }
  }

  return 0;
}
