#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const char nl = '\n';
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);

struct p3d { ld x,y,z; };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d&a,const p3d&b){ return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d&a,const p3d&b){ return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x, s*v.y, s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
	return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
inline p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2) {
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); }
inline p3d rotate(const p3d& p /*pt*/, const p3d& u /*axis*/, const ld& angle) {
  ld c = cos(angle), s = sin(angle), t = 1 - cos(angle);  return {
    p.x*(t*u.x*u.x + c) + p.y*(t*u.x*u.y - s*u.z) + p.z*(t*u.x*u.z + s*u.y),
    p.x*(t*u.x*u.y + s*u.z) + p.y*(t*u.y*u.y + c) + p.z*(t*u.y*u.z - s*u.x),
    p.x*(t*u.x*u.z - s*u.y) + p.y*(t*u.y*u.z + s*u.x) + p.z*(t*u.z*u.z + c) };
}
ostream& operator<< (ostream& os, const p3d& p) {
	return os << "(" << p.x << "," << p.y << "," << p.z << ")";
}

ld dotangle(const p3d& a, const p3d& b) {
	ld da = abs(a);
	ld db = abs(b);
	if(da < EPS || db < EPS) return 0;
	ld val = dot(a, b) / da / db;
	val = min((ld)1, max((ld)-1, val));
	return acos(val);
}

int farthest(const vector<p3d>& p, int s) {
	int n = p.size();
	int res = -1;
	ld maxv = -1;
	for(int i=0; i<n; i++) {
		ld cur = abs(p[i] - p[s]);
		if(cur > maxv) {
			maxv = cur;
			res = i;
		}
	}
	return res;
}

const p3d north = {0,0,1};
const p3d south = {0,0,-1};

void rotate_to_north(vector<p3d>& p) {
	int n = p.size();
	p3d base = p[0];
	if(abs(base-north) > EPS && abs(base-south) > EPS) {
		ld angle = dotangle(base, north);
		p3d axis = cross(base, north);
		axis = axis / abs(axis);
		for(int i=0; i<n; i++) {
			p[i] = rotate(p[i], axis, angle);
		}
	}
}

const int DONE = 1618033988;

ld sgn(const ld& x) {
	return abs(x)<EPS ? 0 : x<0 ? -1 : 1;
}

ld sphere_sgn(const p3d& a, const p3d& b, const p3d& c) {
	p3d pa = pl_inter(b, b, a, a+b);
	p3d pc = pl_inter(b, b, c, c+b);
	if(abs(pa-b) < EPS || abs(pc-b) < EPS) return 0;
	p3d val = cross(pc-b, pa-b) / abs(pc-b) / abs(pa-b);
	return sgn(dot(val, b));
}

ld sphere_ang(const p3d& a, const p3d& b, const p3d& c) {
	p3d pa = pl_inter(b, b, a, a+b);
	p3d pc = pl_inter(b, b, c, c+b);
	return dotangle(pa-b, pc-b);
}

int get_outer(const vector<p3d>& p, vector<pair<ld,int>>& vals) {
	int n = vals.size();
	if(n == 0) return -DONE;
	auto by_dist = [&](const pair<ld,int>& a, const pair<ld,int>& b) {
		if(abs(a.first-b.first) > EPS) return a.first < b.first;
		return abs(p[0]-p[a.second]) < abs(p[0]-p[b.second]);
	};
	sort(vals.begin(), vals.end(), by_dist);

	vector<int> hull = { vals[0].second };
	vals.push_back(vals.front());
	for(int i=1, sz=1; i<=n; i++) {
		while(sz > 1 && sphere_sgn(p[hull[sz-2]], p[hull[sz-1]], p[vals[i].second]) <= 0) {
			hull.pop_back();
			sz--;
		}
		hull.push_back(vals[i].second);
		sz++;
	}

	int l = 0;
	int r = (int)hull.size()-1;
	while(l+1 < r) {
		if(sphere_sgn(p[hull[r]], p[hull[l]], p[hull[l+1]]) < 0) {
			l++;
		} else {
			r--;
		}
	}
	while(clock()<1.7*CLOCKS_PER_SEC);
	return hull[l];
}

pair<int,ld> neighbour(const vector<p3d>& p) {
	int n = p.size();
	vector<pair<ld,int>> vals;
	bool antipodal = false;
	for(int i=0; i<n; i++) {
		if(abs(p[i].x) + abs(p[i].y) < EPS) {
			antipodal |= (abs(p[i]-north) > EPS);
		} else {
			vals.push_back(make_pair(atan2(p[i].y, p[i].x), i));
		}
	}
	sort(vals.begin(), vals.end());

	n = vals.size();
	if(n <= 1 || vals[n-1].first - vals[0].first < EPS) {
		while(clock()<0.5*CLOCKS_PER_SEC);
		return make_pair(DONE, 1);
	}

	int out = -1;
	ld maxv = 0;
	ld second = 0;
	for(int i=0; i<n; i++) {
		int j = (i+1) % n;
		ld d = vals[j].first - vals[i].first;
		if(d < 0) d += 2*PI;
		if(d > maxv) {
			out = vals[j].second;
			second = maxv;
			maxv = d;
		} else if(d > second) {
			second = d;
		}
	}

	// only on great circle
	if(second > PI-EPS) {
		while(clock()<0.7*CLOCKS_PER_SEC);
		return make_pair(DONE, 1);
	}

	// antipodal case
	if(antipodal) {
		if(maxv < PI-EPS) {
			while(clock()<0.6*CLOCKS_PER_SEC);
			return make_pair(DONE, 0);
		} else {
			ld ang = 2*PI - maxv;
			ld ans = 1 - ang*2/(4*PI);
			while(clock()<0.8*CLOCKS_PER_SEC);
			return make_pair(DONE, ans);
		}
	}

	if(maxv < PI-EPS) {
		return make_pair(-get_outer(p, vals), 0);
	} else if(maxv > PI+EPS) {
		return make_pair(out, 0);
	} else {
		return make_pair(out, 0.5);
	}
}

vector<p3d> convex_hull(vector<p3d> p, int s) {
	p3d base = p[0];
	p3d ref = p[s];
	auto by_angle = [&](const p3d& a, const p3d& b) {
		ld av = sphere_ang(ref, base, a);
		ld bv = sphere_ang(ref, base, b);
		if(abs(av-bv) > EPS) return av < bv;
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
	out.pop_back();
	return out;
}

ld area(const vector<p3d>& p) {
	int n = p.size();
	if(n < 3) return 0;
	ld res = 0;
	for(int i=0; i<n; i++) {
		int j = (i+1) % n;
		int k = (i+2) % n;
		res += sphere_ang(p[i], p[j], p[k]);
		//cerr<<" += "<<sphere_ang(p[i],p[j],p[k])<<nl;
	}
	//cerr<<"get area = "<<res<<" - "<<(n-2)<<"*PI = "<<res-(n-2)*PI<<nl;
	return res - (n-2)*PI;
}

ld solve(vector<p3d> p, int base, int redo = 3) {
	swap(p[0], p[base]);
	rotate_to_north(p);
	auto [other, res] = neighbour(p);
	if(other == DONE) {
		return res;
	} else if(other < 0) {
		if(redo) return solve(p, -other, redo-1);
		else return 0;
	} else {
		//cerr<<"other: "<<other<<nl;
		assert(other > 0);
	}

	vector<p3d> hull = convex_hull(p, other);
	//cerr<<"hull: "; for(const p3d& it:hull) {
	//cerr<<it<<"  "; }
	//cerr<<nl;
	if(hull.size() < 3 && abs(res-0.5) < EPS) {
		while(clock()<1.1*CLOCKS_PER_SEC);
		return res;
	}

	ld A = area(hull);
	ld ans = 1 - A/(4*PI);
	ans = max(ans, res);
	if(abs(res-0.5) < EPS) while(clock()<1.2*CLOCKS_PER_SEC);
	assert(abs(res)<EPS || abs(res-0.5)<EPS);
	return ans;
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
	}

	if(n <= 2) {
		cout << 1 << nl;
		return 0;
	}

	int base = 0;
	for(int i=0, j=farthest(p,0); j!=i; ) {
		i = base;
		base = j;
		j = farthest(p,j);
	}

	ld ans = solve(p, base);
	cout << ans << nl;

	return 0;
}
