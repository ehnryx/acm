#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
ld area(const vector<pt> &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return abs(s)/2;}
vector<pt> chull(vector<pt> p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; vector<pt> ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

const ld is_query = -(1LL<<62);
struct Line {
  ld m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ld x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};
// will maintain upper hull for maximum
struct HullDynamic : public multiset<Line> {
  int sgn;
  HullDynamic(int s): sgn(s) {}
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    // could overflow
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
  }
  void insert_line(ld m, ld b) { m *= sgn; b *= sgn;
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ld eval(ld x) {
    auto l = *lower_bound((Line) { x, is_query });
    return sgn * (l.m * x + l.b);
  }
};

HullDynamic upper(-1), lower(1);
ld lb, rb;

void insert_seg(pt a, pt b) {
  if(abs(a.real()-b.real())<EPS) {
    if(a.imag()<b.imag()) rb = min(rb, a.real());
    else lb = max(lb, a.real());
  } else {
    ld M = (a.imag()-b.imag()) / (a.real()-b.real());
    ld B = a.imag() - M * a.real();
    if(abs(arg(b-a)) < M_PIl/2) {
      lower.insert_line(M,B);
    } else {
      upper.insert_line(M,B);
    }
  }
}

ld search(ld left, ld right) {
  for(int bs=0;bs<300;bs++) {
    ld lmid = (2*left+right)/3;
    ld rmid = (left+2*right)/3;
    ld lval = upper.eval(lmid) - lower.eval(lmid);
    ld rval = upper.eval(rmid) - lower.eval(rmid);
    if(lval > rval) {
      right = rmid;
    } else {
      left = lmid;
    }
  }
  return left;
}

ld searchL(ld left, ld right) {
  for(int bs=0;bs<300;bs++) {
    ld mid = (left+right)/2;
    if(lower.eval(mid)>upper.eval(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

ld searchR(ld left, ld right) {
  for(int bs=0;bs<300;bs++) {
    ld mid = (left+right)/2;
    if(lower.eval(mid)>upper.eval(mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return left;
}

pt intersect(int sgn, const Line& u, const Line& v) {
  ld x = (u.b-v.b)/(v.m-u.m);
  ld y = sgn * (u.m*x + u.b);
  return pt(x,y);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin>>T;
  while(T--) {
    lower.clear();
    upper.clear();
    lb = -INF;
    rb = INF;

    int n;
    cin>>n;
    vector<pt> p;
    for(int i=0;i<n;i++) {
      int x,y;
      cin>>x>>y;
      p.push_back(pt(x,y));
    }
    for(int i=0;i<n;i++) {
      insert_seg(p[i],p[(i+1)%n]);
    }
    ld tot = area(p);
    pt half = (p[0]+p[1])/(ld)2;
    pt dir = p[1] - p[0];
    insert_seg(half,half+dir*pt(1,1));
    insert_seg(half+dir*pt(-1,1),half);
    //cerr<<"insert seg "<<half<<" "<<half+dir*pt(1,1)<<nl;
    //cerr<<"insert seg "<<half+dir*pt(-1,1)<<" "<<half<<nl;

    ld mid = search(-INF, INF);
    lb = max(lb, searchL(-INF, mid));
    rb = min(rb, searchR(mid, INF));
    assert(lb < rb);

    p.clear();
    p.push_back(pt(lb,lower.eval(lb)));
    for(auto it=lower.begin(); next(it)!=lower.end(); it++) {
      pt cur = intersect(lower.sgn, *it, *next(it));
      if(lb < cur.real() && cur.real() < rb) {
        p.push_back(cur);
      }
    }
    p.push_back(pt(rb,lower.eval(rb)));
    p.push_back(pt(rb,upper.eval(rb)));
    for(auto it=upper.rbegin(); next(it)!=upper.rend(); it++) {
      pt cur = intersect(upper.sgn, *it, *next(it));
      if(lb < cur.real() && cur.real() < rb) {
        p.push_back(cur);
      }
    }
    p.push_back(pt(lb,upper.eval(lb)));

    ld ans = area(p);
    assert(ans>-EPS);
    cout<<ans/tot<<nl;
  }

  return 0;
}
