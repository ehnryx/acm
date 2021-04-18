#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll inverse(ll n) {
  ll r = 1;
  for(int e=MOD-2; e; e/=2, n = n*n % MOD) {
    if(e&1) r = r*n % MOD;
  }
  return r;
}

struct Frac {
  ll n, d;
  Frac(ll _n=0, ll _d=1) {
    ll g = abs(gcd(_n, _d));
    n  = _n/g; d = _d/g;
    if(d < 0) {
      n = -n;
      d = -d;
    }
  }
  Frac operator + (const Frac& o) const { return Frac(n*o.d + d*o.n, d*o.d); }
  Frac operator - (const Frac& o) const { return Frac(n*o.d - d*o.n, d*o.d); }
  Frac operator * (const Frac& o) const { return Frac(n*o.n, d*o.d); }
  Frac operator / (const Frac& o) const { return Frac(n*o.d, d*o.n); }
  bool operator < (const Frac& o) const { return n*o.d < d*o.n; }
  bool operator == (const Frac& o) const { return n*o.d == d*o.n; }
  bool operator != (const Frac& o) const { return n*o.d != d*o.n; }
};


struct p3d {
  Frac x, y, z;
  bool operator == (const p3d& o) const {
    return x == o.x && y == o.y && z == o.z;
  }
  bool operator != (const p3d& o) const {
    return x != o.x && y != o.y && z != o.z;
  }
};
p3d operator+(const p3d& a, const p3d& b) {
  return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d& a, const p3d& b) {
  return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const Frac &s, const p3d &v){ return {s*v.x,s*v.y,s*v.z}; }
p3d operator/(const p3d&v, const Frac &s){ return {v.x/s, v.y/s, v.z/s}; }
inline Frac dot(const p3d &a, const p3d &b){
  return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2) {
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); }

ostream& operator << (ostream& os, const Frac& v) {
  return os << v.n << "/" << v.d << " = " << (long double)v.n/v.d;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int a, b, c, A, B, C;
    cin >> a >> b >> c >> A >> B >> C;
    vector<Frac> events;
    vector<p3d> verts;
    for(int x : {0, a}) {
      for(int y : {0, b}) {
        for (int z : {0, c}) {
          events.push_back(A*x + B*y + C*z);
          verts.push_back({x, y, z});
        }
      }
    }
    sort(begin(events), end(events));

    p3d o{Frac(a,2), Frac(b,2), Frac(c,2)};
    p3d n{A, B, C};
    int cnt = 0;
    for(const auto& u : verts) {
      for(const auto& v : verts) {
        if(u == v) continue;
        if(u.x != v.x && u.y != v.y) continue;
        if(u.y != v.y && u.z != v.z) continue;
        if(u.z != v.z && u.x != v.x) continue;
        if(dot(n, u-v).n == 0) continue;
        p3d it = pl_inter(o, n, u, v);
        if(Frac(0) < dot(u - v, it - v) && Frac(0) < dot(v - u, it - u)) {
          cnt++;
        }
      }
    }
    //cerr << "cnt = " << cnt << nl;
    vector<int> val = {-1, 0, 1, 2, cnt/2 == 6 ? 3 : 1, 2, 1, 0};

    vector<Frac> ans(4);
    for(int i=1; i<size(events); i++) {
      ans[val[i]] = ans[val[i]] + (events[i] - events[i-1]);
    }
    for(int i=0; i<4; i++) {
      if(i > 0) cout << " ";
      Frac out = ans[i] / (events.back() - events.front());
      cout << (out.n % MOD + MOD) * inverse(out.d % MOD + MOD) % MOD;
    }
    cout << nl;
  }

  return 0;
}
