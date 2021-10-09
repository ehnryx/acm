//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
//typedef long double ld;
//typedef complex<ld> pt;

typedef double ld;
struct pt {
  ld x, y;
  pt(const ld& _x=0, const ld& _y=0): x(_x), y(_y) {}
  pt operator * (const pt& o) const { return pt(x*o.x - y*o.y, x*o.y + y*o.x); }
  pt operator - () const { return pt(-x, -y); }
  pt operator - (const pt& o) const { return pt(x-o.x, y-o.y); };
  pt operator + (const pt& o) const { return pt(x+o.x, y+o.y); };
  pt operator / (const ld& c) const { return pt(x/c, y/c); }
  ld real() const { return x; }
  ld imag() const { return y; }
};
ld real(const pt& a) { return a.x; }
ld imag(const pt& a) { return a.y; }
pt conj(const pt& a) { return pt(a.x, -a.y); }
ld abs(const pt& a) { return sqrt(a.x*a.x + a.y*a.y); }
pt operator * (const ld& c, const pt& a) { return pt(c*a.x, c*a.y); }

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T> ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[";
  for(const T& it : v) {
    os << " " << it << ", ";
  }
  return os << "]";
}

const ld BIG = 500;

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}
ld dp(const pt& a, const pt& b) {
  return real(conj(a) * b);
}

ld area(const vector<pt>& v) {
  int n = v.size();
  ld s = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    s += cp(v[j], v[i]);
  }
  return s;
}

vector<pt> read() {
  int n;
  cin >> n;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back(pt(x, y));
  }
  //////cerr<<"area p: "<<area(p)<<nl;
  //////cerr<<nl;
  if(area(p) < 0) {
    reverse(p.begin(), p.end());
  }
  return p;
}

vector<pt> orient(const vector<pt>& p, int e) {
  int n = p.size();
  pt base = p[e];
  pt odir = p[(e+1)%n] - p[e];
  odir = conj(odir / abs(odir)); // unit direction -> multiply by conjugate to undo

  vector<pt> out(n);
  for(int i=0; i<n; i++) {
    out[i] = (p[i] - base) * odir;
  }
  return out;
}

pair<ld,ld> get_range(pt a, pt b, pt c, pt d) {
  if(a.imag() > b.imag()) swap(a, b);
  if(c.imag() > d.imag()) swap(c, d);
  ld s = max(a.imag(), c.imag());
  ld t = min(b.imag(), d.imag());
  return make_pair(s, t);
}

pt get_point(const pt& a, const pt& b, ld y) {
  if(abs(a.imag() - b.imag()) < EPS) {
    assert(abs(a.imag() - y) < EPS);
    return a;
  } else {
    pt v = (y - a.imag()) / (b.imag() - a.imag()) * (b - a);
    return a + v;
  }
}

enum {
  START_FRONT,
  DONE_FRONT,
  START_ALL,
  DONE_ALL,
  START_BACK,
  DONE_BACK,
  START_BAD,
  DONE_BAD,
  QUERY,
};

struct Event {
  ld x;
  int type;
  ld value;
  Event(ld _x, int t, ld v): x(_x), type(t), value(v) {}
  bool operator < (const Event& o) const {
    if(x != o.x) return x < o.x;
    return type < o.type;
  }
};

vector<pt> reflect(const vector<pt>& p) {
  vector<pt> out;
  for(const pt& v : p) {
    out.push_back(-v);
  }
  return out;
}

// move p, fix q
void push_points(const vector<pt>& p, const vector<pt>& q, vector<Event>& ev) {
  //////cerr<<"PUSH points "<<nl;
  int n = p.size();
  int m = q.size();
  for(int i=0; i<n; i++) {
    const pt& v = p[i];
    for(int j=0; j<m; j++) {
      int nj = (j+1) % m;
      int mj = (j+2) % m;
      const pt& a = q[j];
      const pt& b = q[nj];
      const pt& c = q[mj];
      // a -> b -> c
      ld s = min(a.imag(), b.imag());
      ld t = max(a.imag(), b.imag());
      bool push_start = false;
      bool push_done = false;
      ld x = b.real() - v.real(); // init to nasty case
      if(s + EPS < v.imag() && v.imag() < t - EPS) {
        // in edge
        x = get_point(a, b, v.imag()).real() - v.real();
        if(a.imag() > b.imag()) { // down edge -> enter
          push_start = true;
        } else { // up edge -> exit
          push_done = true;
        }
      } else if(abs(v.imag() - b.imag()) < EPS) {
        // vertices concide
        s = min(a.imag(), c.imag());
        t = max(a.imag(), c.imag());
        if(s - EPS < v.imag() && v.imag() < t + EPS) {
          // normal case
          if(a.imag() > c.imag()) { // down turn -> enter
            if(c.imag() + EPS < v.imag() && v.imag() < a.imag() - EPS) {
              push_start = true;
            } else if(abs(a.imag() - b.imag()) < EPS && a.real() < b.real()) {
              push_start = true;
            } else if(abs(c.imag() - b.imag()) < EPS && c.real() < b.real()) {
              push_start = true;
            }
          } else { // up turn -> exit
            if(a.imag() + EPS < v.imag() && v.imag() < c.imag() - EPS) {
              push_done = true;
            } else if(abs(a.imag() - b.imag()) < EPS && a.real() > b.real()) {
              push_done = true;
            } else if(abs(c.imag() - b.imag()) < EPS && c.real() > b.real()) {
              push_done = true;
            }
          }
        } else if(cp(a-b, c-b) > 0) {
          // corner case
          if(t + EPS < v.imag() || s - EPS > v.imag()) {
            // from bottom or from top
            push_start = true;
            push_done = true;
          }
        }
      }
      if(push_start) {
        ev.push_back(Event(x + EPS, START_BAD, 0));
      }
      if(push_done) {
        ev.push_back(Event(x - EPS, DONE_BAD, 0));
      }
    }
  }
  //////cerr<<nl;
}

// horizontally sweep q from left to right, p is fixed
ld sweep(const vector<pt>& p, const vector<pt>& q) {
  int n = p.size();
  int m = q.size();
  ////cerr<<"SWEEP: "<<nl;
  ////cerr<<"p = "<<p<<nl;
  ////cerr<<"q = "; vector<pt> QQ; for(pt v : q) QQ.push_back(v + BIG);
  ////cerr<<QQ<<nl;

  // vector of events
  vector<Event> ev;

  // intersect edges
  for(int i=0; i<n; i++) {
    int ni = (i+1) % n;
    const pt& a = p[i];
    const pt& b = p[ni];
    for(int j=0; j<m; j++) {
      int nj = (j+1) % m;
      const pt& c = q[j];
      const pt& d = q[nj];
      if(abs(cp(a-b, c-d)) / abs(a-b) < EPS) { // parallel
        if(abs(a.imag() - b.imag()) < EPS) {
          // horizontal
          if(abs(a.imag() - c.imag()) > EPS) continue; // y values don't match
          ld lfix = min(a.real(), b.real());
          ld rfix = max(a.real(), b.real());
          ld lmov = min(c.real(), d.real());
          ld rmov = max(c.real(), d.real());
          ld left = lfix - rmov;
          ld right = rfix - lmov;
          if(dp(a-b, c-d) > 0) { // wrong orientation, this is bad
            ev.push_back(Event(left + EPS, START_BAD, 0));
            ev.push_back(Event(right - EPS, DONE_BAD, 0));
            assert(abs(left - right) > EPS);
          } else {
            ld s = min(lfix - lmov, rfix - rmov);
            ld t = max(lfix - lmov, rfix - rmov);
            // middle part
            ld overlap = min(rfix - lfix, rmov - lmov);
            ev.push_back(Event(s, START_ALL, overlap));
            ev.push_back(Event(t, DONE_ALL, overlap));
            // front part
            ev.push_back(Event(left, START_FRONT, left));
            ev.push_back(Event(s, DONE_FRONT, left));
            // back part
            ev.push_back(Event(t, START_BACK, right));
            ev.push_back(Event(right, DONE_BACK, right));
            // asserts
            //////cerr<<"AT edges "<<a<<" "<<b<<" and "<<c+BIG<<" "<<d+BIG<<nl;
            //////cerr<<" ^ "<<left-BIG<<" "<<s-BIG<<" "<<t-BIG<<" "<<right-BIG<<endl;
            assert(left < s + EPS);
            assert(s < t + EPS);
            assert(t < right + EPS);
          }
        } else {
          // not horizontal
          auto [s, t] = get_range(a, b, c, d);
          if(s > t) continue; // does not overlap
          pt to = get_point(a, b, s);
          pt from = get_point(c, d, s);
          ld x = to.real() - from.real();
          ld overlap = abs(to - get_point(a, b, t));
          if(overlap < EPS) continue; // negligible overlap
          if(dp(a-b, c-d) > 0) { // wrong orientation
            ev.push_back(Event(x - EPS, START_BAD, 0));
            ev.push_back(Event(x + EPS, DONE_BAD, 0));
          } else {
            ev.push_back(Event(x - EPS, START_ALL, overlap));
            ev.push_back(Event(x + EPS, DONE_ALL, overlap));
          }
        }
      } else { // not parallel
        auto [s, t] = get_range(a, b, c, d);
        if(s > t + EPS) continue; // does not touch
        pt s_to = get_point(a, b, s);
        pt s_from = get_point(c, d, s);
        pt t_to = get_point(b, a, t);
        pt t_from = get_point(d, c, t);
        ld left = min(s_to.real() - s_from.real(), t_to.real() - t_from.real());
        ld right = max(s_to.real() - s_from.real(), t_to.real() - t_from.real());
        if(abs(left - right) < EPS) continue; // negligible intersection
        bool push_bad = false;
        if(abs(a.imag() - b.imag()) < EPS) { // ab is horizontal
          if(a.real() < b.real()) { // a -> b
            if(max(c.imag(), d.imag()) > a.imag() + EPS) {
              push_bad = true;
            }
          } else { // b <- a
            if(min(c.imag(), d.imag()) < a.imag() - EPS) {
              push_bad = true;
            }
          }
        } else if(abs(c.imag() - d.imag()) < EPS) { // cd is horizontal
          if(c.real() < d.real()) { // c -> d
            if(max(a.imag(), b.imag()) > c.imag() + EPS) {
              push_bad = true;
            }
          } else { // d <- c
            if(min(a.imag(), b.imag()) < c.imag() - EPS) {
              push_bad = true;
            }
          }
        } else { // neither is horizontal
          push_bad = true;
        }
        if(push_bad) {
          ////////cerr<<"push bad because: "<<a<<" "<<b<<" and "<<c+BIG<<" "<<d+BIG<<nl;
          ev.push_back(Event(left + EPS, START_BAD, 0));
          ev.push_back(Event(right - EPS, DONE_BAD, 0));
        }
      }
    }
  }

  // point of q w/ polygon p
  push_points(q, p, ev);
  // point of p w/ polygon q
  vector<pt> ref_p = reflect(p);
  vector<pt> ref_q = reflect(q);
  push_points(ref_p, ref_q, ev);

  sort(ev.begin(), ev.end());

  ld best = 0;
  ld all = 0;
  ld front = 0;
  ld back = 0;
  int fcnt = 0;
  int bcnt = 0;
  int bad = 0;
  for(auto [x, type, value] : ev) {
    assert(x == x && value == value); // no nans
    //////cerr<<"@ "<<x-BIG<<" "<<type<<" "<<value-BIG<<nl;
    if(!bad) {
      ld frontvalue = fcnt*x - front;
      ld backvalue = back - bcnt*x;
      ld cur = all + frontvalue + backvalue;
      best = max(best, cur);
    }
    if(type == START_ALL) {
      all += value;
    } else if(type == DONE_ALL) {
      all -= value;
    } else if(type == START_FRONT) {
      front += value;
      fcnt++;
    } else if(type == DONE_FRONT) {
      front -= value;
      fcnt--;
    } else if(type == START_BACK) {
      back += value;
      bcnt++;
    } else if(type == DONE_BACK) {
      back -= value;
      bcnt--;
    } else if(type == START_BAD) {
      bad++;
    } else if(type == DONE_BAD) {
      bad--;
    }
    if(!bad) {
      ld frontvalue = fcnt*x - front;
      ld backvalue = back - bcnt*x;
      ld cur = all + frontvalue + backvalue;
      best = max(best, cur);
    }
  }

  assert(bad == 0);
  assert(fcnt == 0);
  assert(bcnt == 0);

  ////cerr<<"Got best = "<<best<<nl<<nl;
  return best;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(12);

  vector<pt> p = read();
  vector<pt> q = read();
  int n = p.size();
  int m = q.size();

  ld ans = 0;
  for(int i=0; i<n; i++) {
    vector<pt> rotp = orient(p, i);
    for(int j=0; j<m; j++) {
      vector<pt> rotq = orient(q, j);
      for(auto& v : rotq) {
        v = -v - BIG;
      }
      ans = max(ans, sweep(rotp, rotq));
    }
  }
  cout << ans << nl;

  return 0;
}
