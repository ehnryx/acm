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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct p3d{ ld x,y,z;
  friend ostream& operator<< (ostream& os, const p3d& p) {
  return os << "(" << p.x << "," << p.y << "," << p.z << ")"; } };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d& a, const p3d& b) {
  return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d& a, const p3d& b) {
  return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x,s*v.y,s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){
  return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }

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
			ld a, b, c;
			cin >> a >> b >> c;
			p.push_back({a, b, c});
		}
		Hull3::build(p);
		ld area = 0;
		ld volume = 0;
		for(const auto& f : Hull3::faces) {
			area += Hull3::area(f);
			volume += Hull3::volume(f);
		}
		cout << area/2 << " " << volume << nl;
	}

	return 0;
}
