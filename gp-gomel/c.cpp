#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int,int>;
using ll = long long;
using ld = long double;
using pt = complex<ld>;
const char nl = '\n';

const ld PI = acos((ld)-1);

struct Point {
	ll x, y;
	Point operator + (const Point& o) const { return { x+o.x, y+o.y }; }
	Point operator - (const Point& o) const { return { x-o.x, y-o.y }; }
	bool operator < (const Point& o) const {
		return x < o.x || (x == o.x && y < o.y);
	}
};

Point sample(const pt& v) {
	return { llround(v.real()), llround(v.imag()) };
}

int sgncp(const Point& a, const Point& b) {
	ll cp = a.x*b.y - a.y*b.x;
	return (cp<0 ? -1 : cp>0 ? 1 : 0);
}

int seg_x_seg(Point a, Point b, Point c, Point d) {
	int s1 = sgncp(a-b, c-b); int s2 = sgncp(a-b, d-b);
	int s3 = sgncp(c-d, a-d); int s4 = sgncp(c-d, b-d);
	if(!s1 && !s2 && !s3) {
		if(b<a) swap(a,b);
		if(d<c) swap(c,d);
		return !(d<a) && !(b<c);
	} return s1*s2 <= 0 && s3*s4 <= 0;
}

void solve(int n, int m, int k) {
	const ld R = 1e5;
	vector<Point> p;
	for(int i=0; i<m; i++) {
		p.push_back(sample(R*exp(pt(0, PI*i/(m-1)))));
	}
	assert(m>=3);

	if(m<n) {
		int ref = k - (m*(m-3)/2 + n-m);
		ref = m-2 - ref;
		assert(ref >= 0);
		if(ref == 0) {
			p.push_back({0, -1789}); // VIVE LA REVOLUTION
		} else {
			assert(ref+1 < p.size());
			Point cur = p[0] - p[ref] + p[0];
			p.push_back({cur.x+(ref==1), cur.y});
		}
		ll lbx = p[0].x;
		for(int i=m+1; i<n; i++) {
			if((i-m)%2) {
				lbx = max(lbx+1, p.back().x);
				p.push_back({lbx, 0});
			} else {
				int sz = p.size();
				Point cur = p[sz-1] - p[sz-2] + p[sz-1];
				p.push_back({cur.x+1, cur.y});
			}
		}
	}

	vector<Point> out, top;
	for(int i=0; i<m; i++) {
		out.push_back(p[i]);
	}
	for(int i=m; i<n; i++) {
		if((i-m)%4 < 2) {
			out.push_back(p[i]);
		} else {
			top.push_back(p[i]);
		}
	}
	reverse(top.begin(), top.end());
	for(const Point& it : top) {
		out.push_back(it);
	}

	assert(out.size() == n);
	for(const Point& it : out) {
		if(abs(it.x)>8e8 || abs(it.y)>8e8) for(;;);
		assert(abs(it.x) < 8e8 && abs(it.y) < 8e8);
		cout << it.x << " " << it.y << nl;
	}

	for(int i=0; i<n; i++) {
		for(int j=0; j<i; j++) {
			if(i == (j+1)%n || j == (i+1)%n) continue;
			assert(!(seg_x_seg(out[i], out[(i+1)%n], out[j], out[(j+1)%n])));
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	for(int m=n; m>=3; m--) {
		if(m*(m-3)/2 + n-m <= k) {
			cout << "Yes" << nl;
			solve(n, m, k);
			return 0;
		}
	}
	assert(k < n-3);
	cout << "No" << nl;

	return 0;
}
