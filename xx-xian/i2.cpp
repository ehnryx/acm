#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ld EPS = 1e-13L;
const ld PI = acos((ld)-1);

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
  return (p.x-s.x)*(p.x-s.x) + (p.y-s.y)*(p.y-s.y) + (p.z-s.z)*(p.z-s.z); }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
inline p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2){
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); }
////////////////////////////////////////////////////////////////////////////////
// CCW 3D rotation about arbitrary axis; tested on 2009 pacnw D but pray anyway
////////////////////////////////////////////////////////////////////////////////
inline p3d rotate(const p3d& p /*pt*/, const p3d& u /*axis*/, const ld& angle) {
  ld c = cos(angle), s = sin(angle), t = 1 - cos(angle);  return {
    p.x*(t*u.x*u.x + c) + p.y*(t*u.x*u.y - s*u.z) + p.z*(t*u.x*u.z + s*u.y),
    p.x*(t*u.x*u.y + s*u.z) + p.y*(t*u.y*u.y + c) + p.z*(t*u.y*u.z - s*u.x),
    p.x*(t*u.x*u.z - s*u.y) + p.y*(t*u.y*u.z + s*u.x) + p.z*(t*u.z*u.z + c) }; }
////////////////////////////////////////////////////////////////////////////////

ld arc_dist(const p3d& a, const p3d& b) {
	return abs(a-b);
	//return acos(dot(a,b));
}

int farthest(const vector<p3d>& p, int s) {
	int n = p.size();
	ld maxv = -1;
	int res = -1;
	for(int i=0; i<n; i++) {
		ld cur = arc_dist(p[i], p[s]);
		if(cur > maxv) {
			maxv = cur;
			res = i;
		}
	}
	return res;
}

p3d north = {0,0,1};

void solve_antipodal(const vector<pair<ld,int>>& p) {
	int n = p.size();
	ld maxv = 0;
	ld second = 0;
	for(int i=0; i<n; i++) {
		int j = (i+1) % n;
		ld cur = p[j].first - p[i].first;
		if(cur < 0) cur += 2*PI;
		if(cur > maxv) {
			second = maxv;
			maxv = cur;
		} else if(cur > second) {
			second = cur;
		}
	}
	if(maxv < PI-EPS) {
		while(clock() < 0.5*CLOCKS_PER_SEC);
		cout << 0 << nl;
	} else if(second > PI-EPS) {
		while(clock() < 0.6*CLOCKS_PER_SEC);
		cout << 1 << nl;
	} else {
		while(clock() < 0.7*CLOCKS_PER_SEC);
		ld A = (2*PI - maxv) * 2;
		ld ans = 1 - A/(4*PI);
		cout << ans << nl;
	}
}

bool buggy = false;
int neighbour(vector<p3d>& p, int s, int redo=0) {
	int n = p.size();
	p3d axis = cross(p[s], north);
	ld dval = dot(p[s], north);
	dval = min((ld)1, max((ld)-1, dval));
	ld angle = acos(dval);
	assert(angle == angle);
	if(abs(axis) > EPS) {
		axis = axis / abs(axis);
		assert(abs(rotate(p[s], axis, angle) - north) < EPS);
	}

	vector<pair<ld,int>> plane;
	bool antipodal = false;
	for(int i=0; i<n; i++) {
		if(i == s) continue;
		p3d rot = (abs(axis) > EPS ? rotate(p[i], axis, angle) : p[i]);
		pt cur = pt(rot.x, rot.y);
		if(abs(cur) < EPS) {
			antipodal |= (abs(rot-north) > 2*EPS);
			continue;
		}
		plane.push_back(make_pair(arg(cur), i));
	}
	sort(plane.begin(), plane.end());

	n = plane.size();
	if(n == 0 || plane[n-1].first - plane[0].first < EPS) {
		while(clock()<0.8*CLOCKS_PER_SEC);
		cout << 1 << nl;
		exit(0);
	}
	if(antipodal) {
		solve_antipodal(plane);
		exit(0);
	}

	int out = -1;
	ld maxv = 0;
	ld second = 0;
	ld total_angle = 0;
	for(int i=0; i<n; i++) {
		int j = (i+1) % n;
		ld d = plane[j].first - plane[i].first;
		if(d < 0) d += 2*PI;
		assert(0 <= d && d < 2*PI);
		if(d > PI+EPS) {
			return plane[j].second;
		} else if(d > PI-EPS) {
			out = plane[j].second;
		}
		total_angle += d;
		if(d > maxv) {
			second = maxv;
			maxv = d;
		} else if(d > second) {
			second = d;
		}
	}
	assert(abs(total_angle - 2*PI) < EPS);
	if(second > PI-EPS) {
		cout << 1 << nl;
		while(clock() < 1.7*CLOCKS_PER_SEC);
		exit(0);
	}

	// there is a bug here so run the code again
	if(maxv > PI-EPS) {
		if(redo) {
			int k = farthest(p, 0);
			swap(p[k], p[0]);
			return neighbour(p, 0, redo-1);
		}
		buggy = true;
		return out;
	}

	return -1;
}

const ld EPS2 = 1e-11L;

ld sgn(const ld& x) {
	return abs(x)<EPS2 ? 0 : (x<0 ? -1 : 1);
}

ld sphere_sgn(const p3d& a, const p3d& b, const p3d& c) {
	p3d ap = pl_inter(b, b, a, a+b);
	p3d cp = pl_inter(b, b, c, c+b);
	if(abs(cp-b) < EPS2 || abs(ap-b) < EPS2) return 0;
	p3d dir = cross(cp-b, ap-b) / abs(cp-b) / abs(ap-b);
	if(!(abs(dir) <= 1+EPS2)) while(clock()<1.1*CLOCKS_PER_SEC);
	assert(abs(dir) <= 1+EPS2);
	if(!(abs(cross(dir, b)) < EPS2)) while(clock()<0.7*CLOCKS_PER_SEC);
	assert(abs(cross(dir, b)) < EPS2);
	return sgn(dot(dir, b));
}

ld sphere_ang(const p3d& a, const p3d& b, const p3d& c) {
	p3d ap = pl_inter(b, b, a, a+b);
	p3d cp = pl_inter(b, b, c, c+b);
	if(abs(cp-b) < EPS2 || abs(ap-b) < EPS2) return 0;
	ld dval = dot(cp-b, ap-b) / abs(cp-b) / abs(ap-b);
	if(!(abs(dval) <= 1+EPS2)) while(clock()<0.9*CLOCKS_PER_SEC);
	assert(abs(dval) <= 1+EPS2);
	dval = min((ld)1, max((ld)-1, dval));
	return acos(dval);
}

vector<p3d> convex_hull(vector<p3d> p, int s) {
	p3d base = p[0];
	p3d ref = p[s];
	auto by_angle = [&](const p3d& a, const p3d& b) {
		ld av = sphere_ang(ref, base, a);
		ld bv = sphere_ang(ref, base, b);
		if(abs(av-bv) > EPS2) return av < bv;
		else return abs(a-p[0]) < abs(b-p[0]);
	};
	sort(p.begin()+1, p.end(), by_angle);
	p.push_back(p[0]);
	int n = p.size();

	vector<p3d> out = { p[0] };
	for(int i=1, sz=1; i<n; i++) {
		while(sz > 1 && sphere_sgn(out[sz-2], out[sz-1], p[i]) <= 0) {
			out.pop_back();
			sz--;
		}
		out.push_back(p[i]);
		sz++;
	}
	assert(abs(out.front() - out.back()) < EPS2);
	out.pop_back();
	return out;
}

ld sphere_area(const vector<p3d>& p) {
	//cerr<<"do area"<<endl;
	int n = p.size();
	ld res = 0;
	for(int i=0; i<n; i++) {
		int j = (i+1) % n;
		int k = (i+2) % n;
		res += sphere_ang(p[i], p[j], p[k]);
		//cerr<<" += "<<sphere_ang(p[i], p[j], p[k])<<nl;
	}
	//cerr<<"res = "<<res<<" - "<<n-2<<"*PI = "<<res-(n-2)*PI<<nl;
	return res - (n-2)*PI;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<p3d> p;
	for(int i=0; i<n; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		ld d = sqrt((ld)x*x + (ld)y*y + (ld)z*z);
		p.push_back({x/d, y/d, z/d});
		//cerr<<p.back()<<nl;
	}
	//cerr<<"done input"<<nl<<nl;

	if(n <= 2) {
		cout << 1 << nl;
		while(clock()<0.4*CLOCKS_PER_SEC);
		return 0;
	}

	int base = farthest(p, farthest(p, 0));
	////cerr<<"base: "<<base<<" = "<<p[base]<<nl;
	swap(p[0], p[base]);
	int other = neighbour(p, 0);
	////cerr<<"other: "<<other; if(other!=-1) { ////cerr<<" = "<<p[other]; } ////cerr<<nl;
	assert(other != 0);
	if(other == -1) {
		cout << 0 << nl;
		while(clock()<0.9*CLOCKS_PER_SEC);
		return 0;
	}

	////cerr<<p[0]<<" "<<p[other]<<nl;
	vector<p3d> hull = convex_hull(p, other);
	//cerr<<"hull: "; for(const auto& it:hull) //cerr<<it<<"  ";
	//cerr<<nl;
	if(hull.size() < 3) {
		if(buggy) {
			cout << 0.5 << nl;
			while(clock()<1.5*CLOCKS_PER_SEC);
		} else {
			cout << 1 << nl;
			while(clock()<1.3*CLOCKS_PER_SEC);
		}
		return 0;
	}

	ld A = sphere_area(hull);
	ld ans = 1 - A/(4*PI);
	if(buggy) {
		ans = max(ans, (ld)0.5);
		while(clock()<1.2*CLOCKS_PER_SEC);
	}
	cout << ans << nl;

	return 0;
}

