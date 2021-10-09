//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct p3d {
  ld x, y, z;
  friend ostream& operator<< (ostream& os, const p3d& p) {
    return os << "(" << p.x << "," << p.y << "," << p.z << ")";
  }
};
p3d operator - (const p3d& a, const p3d& o) { return { a.x-o.x, a.y-o.y, a.z-o.z }; }
p3d operator + (const p3d& a, const p3d& o) { return { a.x+o.x, a.y+o.y, a.z+o.z }; }
p3d operator / (const p3d& a, const ld& c) { return { a.x/c, a.y/c, a.z/c }; }
ld dot(const p3d& a, const p3d& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b) {
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}
ld abs(const p3d& a) { return sqrt(dot(a, a)); }

namespace Hull3 { // change shift and mask values for >1024 verts
  const int S = 10; const int M = (1<<S) - 1;
  struct face{int a, b, c;};
  struct vert{p3d v; int i; operator p3d() const { return v; } };
  vector<face> faces; vector<vert> v; p3d base;
  ld dist(const face& f, const p3d& p) {
    return dot(cross(v[f.b]-v[f.a], v[f.c]-v[f.b]), p-v[f.a]); }
  ld area(const face& f) {
    return abs(cross(v[f.b]-v[f.a], v[f.c]-v[f.a])); }
  ld volume(const face& f) { p3d n=cross(v[f.b]-v[f.a], v[f.c]-v[f.b]);
    return area(f)*dot(n/abs(n), v[f.a])/6; }
  void convex_hull_clean_input(const vector<p3d>& _v) { int n=_v.size();
    v.resize(n); for(int i=0; i<n; i++) v[i] = {_v[i], i};
    shuffle(v.begin(), v.end(), rng);
    base = v[0]; for(int i=0; i<n; i++) v[i].v = v[i] - base;
    for(int i=1;i<n;i++) if(abs(v[i])>EPS) { swap(v[i],v[1]); break; }
    for(int i=2;i<n;i++) if(abs(cross(v[1], v[i])) > EPS) {
      swap(v[i], v[2]); break; }
    for(int i=3; i<n; i++) if(abs(dot(cross(v[1], v[2]), v[i])) > EPS) {
      swap(v[i], v[3]); break; } }
  void build(const vector<p3d>& _v) {
    convex_hull_clean_input(_v); int n = v.size();
    vector<face> f { {0, 1, 2}, {2, 1, 0} };
    for(int i=3; i<n; i++) { vector<face> nxt; set<int> edge;
      for(auto ff : f) { // remove the faces
        if(dist(ff, v[i]) > EPS) { // above
          edge.insert((ff.a << S) | ff.b);
          edge.insert((ff.b << S) | ff.c);
          edge.insert((ff.c << S) | ff.a);
        } else nxt.push_back(ff); }
      for(auto e : edge) { if(!edge.count(((e & M) << S) | (e >> S)))
        nxt.push_back(face{e >> S, e & M, i}); }
      f = nxt; } faces = f;
    //ld ar=0, vo=0; for (auto ff : f) ar += area(ff), vo += volume(ff);
  }
}

ld triple_product(const p3d& a, const p3d& b, const p3d& c) {
  ld A = abs(a), B = abs(b), C = abs(c);
  if(A<EPS || B<EPS || C<EPS) return 0;
  return dot(a/A, cross(b/B, c/C));
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<p3d> p;
    for(int i=0; i<n; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      p.push_back({a,b,c});
    }
    Hull3::build(p);
    for(const p3d& v : p) {
      bool ok = false;
      for(const auto& [a, b, c] : Hull3::faces) {
        const p3d& A = Hull3::v[a] + Hull3::base;
        const p3d& B = Hull3::v[b] + Hull3::base;
        const p3d& C = Hull3::v[c] + Hull3::base;
        if(abs(triple_product(v-A, B-A, C-A)) < EPS) {
          ok = true;
          break;
        }
      }
      cout << (ok ? 'T' : 'F');
    }
    cout << nl;
  }

  return 0;
}
