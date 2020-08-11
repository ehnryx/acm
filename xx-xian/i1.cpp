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
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
// Assumes nondegenerate, i.e. CH is not a line.
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < (int)p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == (int)p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

struct p3d{ ld x,y,z; friend ostream& operator<< (ostream& os, const p3d& p) {
  return os << "(" << p.x << "," << p.y << "," << p.z << ")"; } };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d&a,const p3d&b){ return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d&a,const p3d&b){ return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x, s*v.y, s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
inline ld dist(const p3d &s, const p3d &p) {
	if(abs(s)<EPS) return abs(p);
	if(abs(p)<EPS) return abs(s);
  return acos(dot(s,p)/abs(s)/abs(p)); }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
inline p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2){
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); }
inline p3d rotate(const p3d& p /*pt*/, const p3d& u /*axis*/, const ld& angle) {
  ld c = cos(angle), s = sin(angle), t = 1 - cos(angle);  return {
    p.x*(t*u.x*u.x + c) + p.y*(t*u.x*u.y - s*u.z) + p.z*(t*u.x*u.z + s*u.y),
    p.x*(t*u.x*u.y + s*u.z) + p.y*(t*u.y*u.y + c) + p.z*(t*u.y*u.z - s*u.x),
    p.x*(t*u.x*u.z - s*u.y) + p.y*(t*u.y*u.z + s*u.x) + p.z*(t*u.z*u.z + c) };
}

int farthest(const vector<p3d>& p, int s) {
	int n = p.size();
	ld maxv = -1;
	int res = -1;
	for(int i=0; i<n; i++) {
		ld cur = dist(p[i], p[s]);
		if(cur > maxv) {
			maxv = cur;
			res = i;
		}
	}
	assert(res != -1);
	return res;
}

const p3d north = {0,0,1};
const p3d south = {0,0,-1};
const p3d origin = {0,0,0};

pt project(const p3d& a, const p3d& b) {
	p3d u = cross(b, north);
	ld ang = acos(dot(b, north) / abs(b));
	p3d v = (abs(ang) < EPS ? a : rotate(a, u/abs(u), ang));
	p3d p = pl_inter(south, north, north, v);
	////cerr<<"project "<<a<<" "<<b<<nl;
	////cerr<<"intersect "<<south<<" "<<north<<" w/ "<<north<<" "<<v<<nl;
	////cerr<<u<<" "<<v<<" "<<p<<nl;
	assert(abs(p.z+1) < EPS);
	return pt(p.x, p.y);
}

ld ang_diff(ld a, ld b) {
	////////cerr<<"ang_diff"<<endl;
	ld d = a - b;
	while(d>2*PI) d -= 2*PI;
	while(d<0) d += 2*PI;
	if(abs(d)<EPS || abs(d-2*PI)<EPS) d = 0;
	return d;
}

int neighbour(const vector<p3d>& p, int s) {
	////////cerr<<"neighbou"<<endl;
	int n = p.size();
	vector<pair<ld,int>> v;
	for(int i=0; i<n; i++) {
		if(i==s) continue;
		pt cur = project(p[i], p[s]);
		if(abs(cur) < EPS) return -1;
		v.push_back(make_pair(arg(cur), i));
	}
	sort(v.begin(), v.end());

	n = v.size();
	for(int i=0, j=n-1; i<n; j=i++) {
		//////cerr<<"try "<<v[i].first<<" "<<v[j].first<<nl;
		//////cerr<<"got ang: "<<ang_diff(v[i].second, v[j].second)<<nl;
		if(ang_diff(v[i].first, v[j].first) > PI) {
			return v[i].second;
		}
	}
	return -1;
}

pt to_plane(const p3d& a, const p3d& n) {
	p3d u = cross(n, north);
	ld ang = acos(dot(n, north));
	p3d v = (abs(ang) < EPS ? a : rotate(a, u/abs(u), ang));
	p3d p = pl_inter(south, north, v, v+north);
	////cerr<<"intersect "<<south<<" "<<north<<" w/ line "<<north<<" "<<v<<nl;
	////cerr<<u<<" "<<ang<<" "<<v<<" "<<p<<nl;
	assert(abs(p.z+1) < EPS);
	return pt(p.x, p.y);
}

p3d un_plane(const pt& a) {
	ld h2 = 1 - norm(a);
	assert(h2 > -EPS);
	ld h = sqrt(max((ld)0, h2));
	return {a.real(), a.imag(), h};
}

ld sphere_ang(const p3d& p, const p3d& a, const p3d& b) {
	if(abs(a-p) < EPS || abs(b-p) < EPS) return 0;
	pt u = project(a, p);
	pt v = project(b, p);
	if(abs(u)<EPS || abs(v)<EPS) return 0;
	return acos(dp(u,v) / abs(u) / abs(v));
}

int sgn(const ld& x) {
	return abs(x)<EPS ? 0 : (x<0 ? -1 : 1);
}

ld sphere_sgn(const p3d& p, const p3d& a, const p3d& b) {
	if(abs(a-p) < EPS || abs(b-p) < EPS) return 0;
	pt u = project(a, p);
	pt v = project(b, p);
	if(abs(u)<EPS || abs(v)<EPS) return 0;
	return sgn(cp(u,v));
}

p3d s_base, s_other;
bool by_angle(const p3d& a, const p3d& b) {
	return sphere_ang(s_base, s_other, a) < sphere_ang(s_base, s_other, b);
}

vector<p3d> convex_hull(vector<p3d> p, int s, int t) {
	s_base = p[s];
	s_other = p[t];
	sort(p.begin(), p.end(), by_angle);
	p.push_back(p.front());

	//cerr<<"sorted: "<<nl; for(const p3d& it:p) //cerr<<it<<"  ";
	//cerr<<nl;

	int n = p.size();
	assert(n >= 4);
	vector<p3d> out = {p[0], p[1]};
	for(int i=2; i<n; i++) {
		int sz = out.size();
		while(sz >= 2 && sphere_sgn(out[sz-1], out[sz-2], p[i]) > 0) {
			out.pop_back();
			sz--;
		}
		out.push_back(p[i]);
	}
	out.pop_back();

	//cerr<<"convex hull: "; for(const p3d& it:out) //cerr<<it<<"  ";
	//cerr<<nl;

	return out;
}

ld area(const vector<p3d>& p) {
	int n = p.size();
	ld tot = 0;
	for(int i=0; i<n; i++) {
		int j = (i+1) % n;
		int k = (i+2) % n;
		ld cur = sphere_ang(p[j], p[i], p[k]);
		assert(cur > -EPS);
		tot += cur;
	}
	//cerr<<"tot: "<<tot<<nl;
	//cerr<<" -> "<<tot-(n-2)*PI<<nl;
	assert(tot - (n-2)*PI > EPS);
	return tot - (n-2)*PI;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<p3d> sphere;
	for(int i=0; i<n; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		ld d = sqrt((ld)x*x + (ld)y*y + (ld)z*z);
		sphere.push_back({x/d, y/d, z/d});
	}

	if(n <= 2) {
		cout << 1 << nl;
		return 0;
	}

	int base = farthest(sphere, farthest(sphere, 0));
	int other = neighbour(sphere, base);
	assert(other != base);
	//cerr<<"base: "<<base<<" other: "<<other<<nl;
	if(other == -1) {
		cout << 0 << nl;
		return 0;
	}

	vector<p3d> hull = convex_hull(sphere, base, other);
	ld A = area(hull);
	ld ans = 1 - A / (4*PI);
	assert(ans < 1+EPS && ans > -EPS);
	cout << ans << nl;

	return 0;
}
